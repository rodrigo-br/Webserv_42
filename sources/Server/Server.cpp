#include "classes/Server.hpp"

void Server::signalHandler(int signum)
{
	(void)signum;
	Server::gSignalInterrupted = true;
}

void Server::runServer(Socket socket)
{
	listenSockets = socket.getlistenSockets();
	signal(SIGINT, Server::signalHandler);
	while (!gSignalInterrupted)
	{
		fd_set read_sockets = socket.getReadFds();
		fd_set write_sockets = socket.getWriteFds();

		if (Utils::check(select(FD_SETSIZE, &read_sockets, &write_sockets,NULL, NULL), "Select"))
		{
			break ;
		}
		for (std::vector<int>::iterator it = listenSockets.begin(); it != listenSockets.end(); ++it)
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
				else
                {
                    std::cout << "Falha ao aceitar novo cliente" << std::endl;
                }
			}
		}
		for (size_t i = 0; i < this->clienstSocks.size(); ++i)
		{
			RequestValidator requestValidator;
	   		Request request ;
			int client_sock = this->clienstSocks[i];
			if (FD_ISSET(client_sock, &read_sockets))
			{
				 std::cout << "Lendo requisição do cliente" << std::endl;

				request = Request().createParsedMessage(client_sock);
				std::cout << request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
				requestValidator = RequestValidator().requestValidator(this->conf.getServersData()[std::atoi(request.getHeader("Host").substr(10).c_str())], request);
				FD_CLR(client_sock, &read_sockets);
				FD_SET(client_sock, &write_sockets);
			}
			if (FD_ISSET(client_sock, &write_sockets))
			{
					std::cout << "Enviando resposta para o cliente" << std::endl;

				Response response(new ResponseBuilder(request, requestValidator));

				if (Utils::check(send(client_sock, response.getResponse(), response.getSize(), 0), "Send"))
				{
					break;
				}
				if (response.hasBody())
				{
					if (Utils::check(send(client_sock, response.getBody(), response.bodySize(), 0), "Send body"))
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

Server::Server(Conf &config) : conf(config)
{
	Socket socket(conf.getServersData());
	if(!socket.succeed())
		return;
	runServer(socket);
}

bool Server::gSignalInterrupted = false;
