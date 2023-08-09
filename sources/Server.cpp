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
	FD_ZERO(&this->currentSockets);
	this->maxSocketSoFar = 0;

	for (std::map<int, ServerData>::const_iterator it = conf.getServersData().begin(); it != conf.getServersData().end(); ++it)
	{
		int port = it->first;
		int sockfd = createSocket();
		setSocketReusable(sockfd);
		sockaddr_in sockaddr = createSockaddr(port);
		bindSocket(sockfd, sockaddr);
		listenSocket(sockfd);

		this->listenSockets.push_back(sockfd);
		FD_SET(sockfd, &this->currentSockets);

		if (sockfd > this->maxSocketSoFar)
		{
			this->maxSocketSoFar = sockfd;
		}
	}
	signal(SIGINT, Server::signalHandler);
	while (!gSignalInterrupted)
	{
		fd_set read_sockets = this->currentSockets;

		if (Utils::check(select(FD_SETSIZE, &read_sockets, NULL,NULL, NULL)))
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
				int new_socket = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);

				if (new_socket != -1)
				{
					std::cout << "Accepted connection on port " << ntohs(client_addr.sin_port) << std::endl;
					Request request = Request().createParsedMessage(new_socket);

					std::cout << request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
					RequestValidator requestValidator = RequestValidator().requestValidator(this->conf.getServersData()[std::atoi(request.getHeader("Host").substr(10).c_str())], request);

					Response response(new ResponseBuilder(request, requestValidator));

					send(new_socket, response.getResponse(), response.getSize(), 0);
					if (response.hasBody())
					{
						send(new_socket, response.getBody(), response.bodySize(), 0);
					}
					close(new_socket);
					FD_CLR(new_socket, &this->currentSockets);

				}
			}
		}
	}
	this->conf.deleteConfParser();
}

bool Server::gSignalInterrupted = false;
