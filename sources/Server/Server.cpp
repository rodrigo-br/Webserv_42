#include "classes/Server.hpp"

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
		close(clienstSocks[i]);
	}
}
bool endsWith(const std::string &str, const std::string &suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}
void Server::sendClientResponse(int clientSocket, int i, Request &request, RequestValidator &validator) 
{
	ServerData server2;
	std::string cgi = "/cgi-bin";
	 if (!server2.getLocation(cgi).empty())
	 {
		if (endsWith(request.getPath() , ".php")) {
			Cgi CgiRequest(request, validator);
			std::string result = CgiRequest.executeCgi();
			request.setBody(result);
		}
	 }
	 std::cout << "Sending response to client" << std::endl;
	

	Response response(new ResponseBuilder(request, validator));

	if (Utils::check(send(clientSocket, response.getResponse(), response.getSize(), 0), "Send")) 
	{
		return;
	}
	if (response.hasBody()) 
	{
		if (Utils::check(send(clientSocket, response.getBody(), response.bodySize(), 0), "Send body")) 
		{
			return;
		}
	}

	FD_CLR(clientSocket, &this->writeSocket);
	FD_SET(clientSocket, &this->readSocket);
	close(clientSocket);
	clienstSocks.erase(clienstSocks.begin() + i);
}

void Server::processClientRequest(int clientSocket, Request &request, RequestValidator &validator) 
{

	std::cout << "Reading client request" << std::endl;
	request = Request().createParsedMessage(clientSocket);
	std::cout << request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
	
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
			processClientRequest(clientSocket, request, requestValidator);
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

	while (!gSignalInterrupted) 
	{
		this->readSocket = socket.getReadFds();
		this->writeSocket = socket.getWriteFds();

		if (Utils::check(select(FD_SETSIZE, &this->readSocket, &this->writeSocket, NULL, NULL), "Select")) 
		{
			break;
		}
		handleNewClients();
		processClients();
	}

	closeSockets();
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
