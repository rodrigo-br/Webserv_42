#include "classes/Server.hpp"
#include <vector>
#include <algorithm>

static int create_socket(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (Utils::check(sockfd))
	{
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

static sockaddr_in create_sockaddr(int port)
{
	sockaddr_in _sockaddr;
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(port);
	return (_sockaddr);
}

static void bind_socket(int &sockfd, sockaddr_in &sockaddr)
{
	if (Utils::check(bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))))
	{
		exit(EXIT_FAILURE);
	}
}

static void listen_socket(int &sockfd)
{
	if (Utils::check(listen(sockfd, 10)))
	{
		exit(EXIT_FAILURE);
	}
}

static void set_socket_reusable(int sockfd)
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
	FD_ZERO(&this->current_sockets);
	this->max_socket_so_far = 0;

	for (std::map<int, ServerData>::const_iterator it = conf.getServersData().begin(); it != conf.getServersData().end(); ++it)
	{
		int port = it->first;
		int sockfd = create_socket();
		set_socket_reusable(sockfd);
		sockaddr_in sockaddr = create_sockaddr(port);
		bind_socket(sockfd, sockaddr);
		listen_socket(sockfd);

		this->listen_sockets.push_back(sockfd);
		FD_SET(sockfd, &this->current_sockets);

		if (sockfd > this->max_socket_so_far)
		{
			this->max_socket_so_far = sockfd;
		}
	}
	signal(SIGINT, Server::signalHandler);
	while (!gSignalInterrupted)
	{
		fd_set read_sockets = this->current_sockets;

		if (Utils::check(select(FD_SETSIZE, &read_sockets, NULL,NULL, NULL)))
		{
			break ;
		}

		for (std::vector<int>::iterator it = this->listen_sockets.begin(); it != this->listen_sockets.end(); ++it)
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
					Request request = Request().create_parsed_message(new_socket);

					std::cout << request.get_mensage_request() << std::string(42, '-') << '\n' << std::endl;
					RequestValidator request_validator = RequestValidator().request_validator(this->conf.getServersData()[std::atoi(request.get_header("Host").substr(10).c_str())], request);

					Response response(new ResponseBuilder(request, request_validator));

					send(new_socket, response.get_response(), response.get_size(), 0);
					if (response.has_body())
					{
						send(new_socket, response.get_body(), response.body_size(), 0);
					}
					close(new_socket);
					FD_CLR(new_socket, &this->current_sockets);

				}
			}
		}
	}
	this->conf.deleteConfParser();
}

bool Server::gSignalInterrupted = false;
