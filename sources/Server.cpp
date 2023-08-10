#include "classes/Server.hpp"
#include <vector>
#include <algorithm>

static int create_socket(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (Utils::check(sockfd))
	{
		close(sockfd);
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
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

static void listen_socket(int &sockfd)
{
	if (Utils::check(listen(sockfd, 10)))
	{
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

static void set_socket_reusable(int sockfd)
{
	int optval = 1;
	if (Utils::check(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))))
	{
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

void Server::signalHandler(int signum)
{
	(void)signum;
	Server::gSignalInterrupted = true;
}

#include <fcntl.h>



Server::Server(Conf &config) : conf(config)
{
	std::vector<int> ports;
	ports.push_back(8000);
	ports.push_back(8080);
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	max_socket_so_far = 0;
	int sockfd; 
	for (std::vector<int>::const_iterator it = ports.begin(); it != ports.end(); ++it) {
		sockfd = create_socket();
		set_socket_reusable(sockfd);
		int port = *it;
		sockaddr_in sockaddr = create_sockaddr(port);
		bind_socket(sockfd, sockaddr);
		listen_socket(sockfd);
		if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
        {
			close(sockfd);
            exit(EXIT_FAILURE);
        }
		FD_SET(sockfd, &read_fds);
		listen_sockets.push_back(sockfd);
	}
	signal(SIGINT, Server::signalHandler);
	while (true)
	{
		fd_set read_sockets = read_fds;
		fd_set write_sockets = write_fds;
		if (Utils::check(select(FD_SETSIZE, &read_sockets, &write_sockets,NULL, NULL)))
			break ;
		for (std::vector<int>::iterator it = listen_sockets.begin(); it != listen_sockets.end(); ++it)
		{
			int sockfd_it = *it;
			if (FD_ISSET(sockfd_it, &read_sockets))
			{   
				sockaddr_in client_addr;
				socklen_t addr_len = sizeof(client_addr);
				int client_sock = accept(sockfd_it, (struct sockaddr*)&client_addr, &addr_len);
				if (client_sock != -1)
				{
					request = Request().create_parsed_message(client_sock);
					std::cout << request.get_mensage_request() << std::string(42, '-') << '\n' << std::endl;
					request_validator = RequestValidator().request_validator(this->conf, request);
					FD_SET(client_sock, &write_sockets);
					client_socks.push_back(client_sock);
				}
			}
		}
		for (size_t i = 0; i < client_socks.size(); ++i)
    	{
			int client_sock = client_socks[i];
			if (FD_ISSET(client_sock, &write_sockets))
			{
				Response response(new ResponseBuilder(request, request_validator));
				if (Utils::check(send(client_sock, response.get_response(), response.get_size(), 0)))
					break;
				if (response.has_body()) 
					if (Utils::check(send(client_sock, response.get_body(), response.body_size(), 0)))
						break;
       		}
			FD_CLR(client_sock, &read_sockets);
			close(client_sock);
			client_socks.erase(client_socks.begin() + i);
			--i;
		}
	}
		
	for (size_t i = 0; i < listen_sockets.size(); ++i)
	{
		close(listen_sockets[i]);
	}
	for (size_t i = 0; i < client_socks.size(); ++i)
	{
		close(client_socks[i]);
	}
	this->conf.deleteConfParser();
}



////////////////////////////////////////////////////////////////////////////


// Server::Server(Conf &config) : conf(config)
// {
// 	std::vector<int> ports;
// 	ports.push_back(8000);
// 	ports.push_back(8080);
// 	ports.push_back(65535);
// 	ports.push_back(65536);
// 	ports.push_back(1024);
// 	ports.push_back(6664);
// 	ports.push_back(6668);
// 	ports.push_back(56666);
// 	FD_ZERO(&read_fds);
// 	max_socket_so_far = 0;

// 	for (std::vector<int>::const_iterator it = ports.begin(); it != ports.end(); ++it) {
// 		int port = *it;
// 		int sockfd = create_socket();
// 		set_socket_reusable(sockfd);
// 		sockaddr_in sockaddr = create_sockaddr(port);
// 		bind_socket(sockfd, sockaddr);
// 		listen_socket(sockfd);

// 		listen_sockets.push_back(sockfd);
// 		FD_SET(sockfd, &read_fds);

// 		if (sockfd > max_socket_so_far) {
// 			max_socket_so_far = sockfd;
// 		}
// 	}
// 	signal(SIGINT, Server::signalHandler);
// 	while (!gSignalInterrupted)
// 	{
// 		fd_set read_sockets = read_fds;

// 		if (Utils::check(select(FD_SETSIZE, &read_sockets, NULL,NULL, NULL)))
// 		{
// 			break ;
// 		}

// 		for (std::vector<int>::iterator it = listen_sockets.begin(); it != listen_sockets.end(); ++it)
// 		{
// 			int sockfd = *it;
// 			if (FD_ISSET(sockfd, &read_sockets))
// 			{
// 				sockaddr_in client_addr;
// 				socklen_t addr_len = sizeof(client_addr);
// 				int new_socket = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);

// 				if (new_socket != -1)
// 				{
// 					std::cout << "Accepted connection on port " << ntohs(client_addr.sin_port) << std::endl;
// 					Request request = Request().create_parsed_message(new_socket);
// 					std::cout << request.get_mensage_request() << std::string(42, '-') << '\n' << std::endl;
// 					RequestValidator request_validator = RequestValidator().request_validator(this->conf, request);

// 					Response response(new ResponseBuilder(request, request_validator));

// ssize_t bytes_sent = send(new_socket, response.get_response(), response.get_size(), 0);
//        			if (bytes_sent == -1) {
//             		perror("Erro ao enviar resposta");
//         		} 
// 				else if (bytes_sent > 0) 
// 				{
// 					if (response.has_body()) {
// 						ssize_t bytes_body_sent = send(new_socket, response.get_body(), response.body_size(), 0);
// 						if (bytes_body_sent == -1) {
// 							perror("Erro ao enviar corpo da resposta");
// 						}
// 					}
//        			 }
// 					close(new_socket);
// 					FD_CLR(new_socket, &read_fds);

// 				}
// 			}
// 		}
// 	}
// 	this->conf.deleteConfParser();
// }
bool Server::gSignalInterrupted = false;