#include "classes/Server.hpp"

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

static int accept_socket(int &sockfd, sockaddr_in &sockaddr, int &addrlen)
{
	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (Utils::check(connection))
	{
		exit(EXIT_FAILURE);
	}
	return connection;
}

void Server::signalHandler(int signum) {
	(void)signum;
    Server::gSignalInterrupted = true;
}

Server::Server()
{
	int sockfd = create_socket();
	set_socket_reusable(sockfd);
	sockaddr_in sockaddr = create_sockaddr(this->conf.get_listen());
	bind_socket(sockfd, sockaddr);
	listen_socket(sockfd);
	int addrlen = sizeof(sockaddr);
	signal(SIGINT, Server::signalHandler);

	while(1)
	{
		if (this->gSignalInterrupted)
		{
			break ;
		}
		int connection = accept_socket(sockfd, sockaddr, addrlen);
		Request request = Request().create_parsed_message(connection);
		std::cout << request.get_mensage_request() << std::string(42, '-') << '\n' << std::endl;
		RequestValidator request_validator = RequestValidator().request_validator(this->conf, request);


		send(connection, this->response.get_response(), this->response.get_size(), 0);
		if (this->response.has_body())
		{
			send(connection, this->response.get_body(), this->response.body_size(), 0);
		}
		close(connection);
	}
	close(sockfd);
}

Server::Server()
{
    int sockfd = create_socket();
    set_socket_reusable(sockfd);
    sockaddr_in sockaddr = create_sockaddr(this->conf.get_listen());
    bind_socket(sockfd, sockaddr);
    listen_socket(sockfd);
    int addrlen = sizeof(sockaddr);
    signal(SIGINT, Server::signalHandler);
    int max_socket_so_far = sockfd;
    fd_set current_sockets, read_sockets;
    FD_ZERO(&current_sockets);
    FD_SET(sockfd, &current_sockets);

    while (!gSignalInterrupted)
    {
        read_sockets = current_sockets;
		if (Utils::check(select(FD_SETSIZE, &read_sockets, NULL,NULL, NULL)))
			exit(EXIT_FAILURE);
        for (int i = 0; i <= max_socket_so_far; i++)
        {
            if (FD_ISSET(i, &read_sockets))
            {
                if (i == sockfd)
                {
                    int connection = accept_socket(sockfd, sockaddr, addrlen);
                    FD_SET(connection, &current_sockets);
                    if (connection > max_socket_so_far)
                        max_socket_so_far = connection;
                }
                else
                {
                    Request request = Request().create_parsed_message(i);
                    std::cout << request.get_mensage_request() << std::string(42, '-') << '\n' << std::endl;
                    RequestValidator request_validator = RequestValidator().request_validator(this->conf, request);

                    send(i, this->response.get_response(), this->response.get_size(), 0);
                    if (this->response.has_body())
                    {
                        send(i, this->response.get_body(), this->response.body_size(), 0);
                    }
                    close(i);
                    FD_CLR(i, &current_sockets);
                }
            }
        }
    }

    close(sockfd);
}

bool Server::gSignalInterrupted = false;
