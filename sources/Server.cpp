#include "classes/Server.hpp"
#include <vector>
#include <algorithm>

static int createSocket(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (Utils::check(sockfd))
	{
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

static sockaddr_in createSockaddr(int port)
{
	sockaddr_in _sockaddr;
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(port);
	return (_sockaddr);
}

static void bindSocket(int &sockfd, sockaddr_in &sockaddr)
{
	if (Utils::check(bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))))
	{
		exit(EXIT_FAILURE);
	}
}

static void listenSocket(int &sockfd)
{
	if (Utils::check(listen(sockfd, 10)))
	{
		exit(EXIT_FAILURE);
	}
}

static void setSocketReusable(int sockfd)
{
	int optval = 1;
	if (Utils::check(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))))
	{
		exit(EXIT_FAILURE);
	}
}

void Server::signalHandler(int signum)
{
	(void)signum;
	Server::gSignalInterrupted = true;
}


Server::Server(Conf &config) : conf(config)
{
	FD_ZERO(&this->read_fds);
	FD_ZERO(&this->write_fds);
	int serveSocket;
	for (std::map<int, ServerData>::const_iterator it = conf.getServersData().begin(); it != conf.getServersData().end(); ++it)
	{
		int port = it->first;
		serveSocket = createSocket();
		setSocketReusable(serveSocket);
		sockaddr_in sockaddr = createSockaddr(port);
		bindSocket(serveSocket, sockaddr);
		listenSocket(serveSocket);
		if (Utils::check(fcntl(serveSocket, F_SETFL, O_NONBLOCK)))
		{
			close(serveSocket);
			break ;
		}
		FD_SET(serveSocket, &this->read_fds);
		this->listenSockets.push_back(serveSocket);
	}
	signal(SIGINT, Server::signalHandler);
	while (!gSignalInterrupted)
	{
		fd_set read_sockets = this->read_fds;
		fd_set write_sockets = this->write_fds;

		if (Utils::check(select(FD_SETSIZE, &read_sockets, &write_sockets,NULL, NULL)))
		{
			break ;
		}
		for (std::vector<int>::iterator it = this->listenSockets.begin(); it != this->listenSockets.end(); ++it)
		{
			int sockfd = *it;
			if (FD_ISSET(sockfd, &read_sockets))
			{
				sockaddr_in client_addr;
				socklen_t addr_len = sizeof(client_addr);
				int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);

				if (client_sock != -1)
				{
					FD_SET(client_sock, &read_sockets);
					this->clienstSocks.push_back(client_sock);
				}
			}
		}
		for (size_t i = 0; i < this->clienstSocks.size(); ++i)
		{
			int client_sock = this->clienstSocks[i];
			if (FD_ISSET(client_sock, &read_sockets))
			{
				this->request = Request().createParsedMessage(client_sock);
				std::cout << this->request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
				this->requestValidator = RequestValidator().requestValidator(this->conf.getServersData()[std::atoi(request.getHeader("Host").substr(10).c_str())], request);
				FD_CLR(client_sock, &read_sockets);
				FD_SET(client_sock, &write_sockets);
			}
			if (FD_ISSET(client_sock, &write_sockets))
			{
				Response response(new ResponseBuilder(request, this->requestValidator));

				if (Utils::check(send(client_sock, response.getResponse(), response.getSize(), 0)))
				{
					break;
				}
				if (response.hasBody())
				{
					if (Utils::check(send(client_sock, response.getBody(), response.bodySize(), 0)))
					{
						break;
					}
				}
				FD_CLR(client_sock, &write_sockets);
				FD_SET(client_sock, &read_sockets);
				close(client_sock);
				clienstSocks.erase(clienstSocks.begin() + i);
				--i;
			}

		}
	}
	for (size_t i = 0; i < this->listenSockets .size(); ++i)
	{
		close(listenSockets[i]);
	}
	for (size_t i = 0; i < clienstSocks.size(); ++i)
	{
		close(clienstSocks[i]);
	}
	this->conf.deleteConfParser();
}

bool Server::gSignalInterrupted = false;
