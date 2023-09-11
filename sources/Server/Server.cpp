#include "classes/Server.hpp"

Server::Server(Conf &config) : conf(config), isErrorRead(false)
{
	Socket socket(conf.getServersData());
	if(!socket.succeed())
		return;
	runServer(socket);
}

void Server::signalHandler(int signum)
{
	(void)signum;
	Server::gSignalInterrupted = true;
}

void Server::closeSockets()
{
	for (size_t i = 0; i < this->listenSockets.size(); ++i)
	{
		close(listenSockets[i]);

	}
	for (size_t i = 0; i < clienstSocks.size(); ++i)
	{
		FD_CLR(clienstSocks[i], &this->writeSocket);
		close(clienstSocks[i]);
	}
}

void Server::sendClientResponse(int clientSocket, int i, Request &request, RequestValidator &validator)
{
	std::cout << "Sending response to client" << std::endl;


	Response response(new ResponseBuilder(request, validator));
	std::cout << std::endl<<  "response ===== "<< response.getResponse() << std::endl << std::endl;
	if (Utils::checkSend(send(clientSocket, response.getResponse(), response.getSize(), 0), "Send"))
	{
		close(clientSocket);
		clienstSocks.erase(clienstSocks.begin() + i);
		return;
	}
	if (response.hasBody())
	{
		if (Utils::checkSend(send(clientSocket, response.getBody(), response.bodySize(), 0), "Send body"))
		{
			close(clientSocket);
			clienstSocks.erase(clienstSocks.begin() + i);
			return;
		}
	}
	FD_CLR(clientSocket, &this->writeSocket);
	FD_SET(clientSocket, &this->readSocket);
	close(clientSocket);
	clienstSocks.erase(clienstSocks.begin() + i);
}


void Server::processClientRequest(int clientSocket, int i, Request &request, RequestValidator &validator)
{
	std::cout << "Reading client request" << std::endl;
	request = Request().createParsedMessage(clientSocket, this->isErrorRead);
	if (this->isErrorRead)
	{
		close(clientSocket);
		clienstSocks.erase(clienstSocks.begin() + i);
		return ;
	}
	std::cout << "****************************mensagem gerada**************************" << std::endl;
	std::cout << request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
	std::string cgi = "/cgi-bin";
	if (!this->conf.getLocation(request.getPortNumber(), cgi).empty())
	{
		std::string query = request.getQuery();
		size_t querySymbolPos = request.getPath().find_first_of("?");
		std::string name = "";
		if (querySymbolPos != std::string::npos)
		{
			request.setPath(request.getPath().substr(0, querySymbolPos));
		}
		if (Utils::hasQuery(query, "name=") && request.getMethod() == "POST")
		{
			size_t startPos = query.find("name=");
			std::string restOfQuery = query.substr(startPos);
			size_t endPos = restOfQuery.find_first_of("&");
			name = query.substr(startPos + 5, endPos - 5);
			Cgi CgiRequest(request, this->conf.getRoot(request.getPortNumber()), name);
			CgiRequest.executeCgi();
			request.buildCGI();
			request.setMethod("GET");
		}
		else if (Utils::endsWith(request.getPath() , ".py"))
		{
			Cgi CgiRequest(request, this->conf.getRoot(request.getPortNumber()));
			CgiRequest.executeCgi();
			request.buildCGI();
		}
	}
	validator = RequestValidator().requestValidator(this->conf.getServersData()[request.getPortNumber()], request);
	FD_CLR(clientSocket, &this->readSocket);
	FD_SET(clientSocket, &this->writeSocket);
}


void Server::processClients()
{
	for (size_t i = 0; i < this->clienstSocks.size(); ++i)
	{
		RequestValidator requestValidator;
		Request request;
		int clientSocket = this->clienstSocks[i];
		if (FD_ISSET(clientSocket, &this->readSocket))
		{
			processClientRequest(clientSocket, i,  request, requestValidator);
		}
		if (FD_ISSET(clientSocket, &writeSocket))
		{
			sendClientResponse(clientSocket, i, request, requestValidator);
		}
	}
}

void Server::acceptNewClient(int sockfd)
{
	sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int clientSocket = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);

	if (clientSocket != -1)
	{
		FD_SET(clientSocket, &this->readSocket);
		this->clienstSocks.push_back(clientSocket);
	}
	else
	{
		std::cout << "Failed to accept new client" << std::endl;
	}
}

void Server::handleNewClients()
{
	for (std::vector<int>::iterator it = listenSockets.begin(); it != listenSockets.end(); ++it)
	{
		int sockfd = *it;
		if (FD_ISSET(sockfd, &this->readSocket))
		{
			acceptNewClient(sockfd);
		}
	}
}

void Server::runServer(Socket socket)
{
	listenSockets = socket.getlistenSockets();
	signal(SIGINT, Server::signalHandler);
	struct timeval timer;

	while (!gSignalInterrupted)
	{
		timer.tv_sec = 1;
        timer.tv_usec = 0;
		this->readSocket = socket.getReadFds();
		this->writeSocket = socket.getWriteFds();

		if (Utils::check(select(FD_SETSIZE, &this->readSocket, &this->writeSocket, NULL, &timer), "Select"))
		{
			break;
		}
		handleNewClients();
		processClients();
	}

	closeSockets();
	this->conf.deleteConfParser();
}



bool Server::gSignalInterrupted = false;