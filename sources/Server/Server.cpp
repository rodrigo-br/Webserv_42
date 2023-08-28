#include "classes/Server.hpp"
#define CONNECTION_TIMEOUT 60

void Server::signalHandler(int signum)
{
	(void)signum;
	Server::gSignalInterrupted = true;
}

Server::~Server()
{
	closeSockets();
}

time_t Server::getLastTime()
{
	return _last_msg_time;
}

void             Server::updateTime()
{
    _last_msg_time = time(NULL);
}

void Server::closeSockets()
{
	if (!listenSockets.empty())
    {
		for (int i = this->listenSockets.size() -1; i >= 0; --i)
		{
			close(listenSockets[i]);
			
		}
		listenSockets.clear();
	}
	// for (size_t i = 0; i < clienstSocks.size(); ++i)
	// {
	// 	close(clienstSocks[i]);
	// }
	// FD_CLR(this->readSocket);
	// FD_CLR(this->writeSocket);
}

void Server::sendClientResponse(int clientSocket, int i, Request &request, RequestValidator &validator) 
{
	std::cout << "Sending response to client" << std::endl;
	

	Response response(new ResponseBuilder(request, validator));

	if (Utils::check(send(clientSocket, response.getResponse(), response.getSize(), 0), "Send"))
	{
		close(clientSocket);
		return;
	}
	if (response.hasBody())
	{
		if (Utils::check(send(clientSocket, response.getBody(), response.bodySize(), 0), "Send body"))
		{
			close(clientSocket);
			return;
		}
	}
	updateTime();

	FD_CLR(clientSocket, &this->writeSocket);
	FD_SET(clientSocket, &this->readSocket);
	// close(clientSocket);
    // std::map<int, long int>::iterator it = clienstSocks.begin();
    // std::advance(it, i);
    // clienstSocks.erase(it);
	// closeConnection(clientSocket);
	(void)i;
}


void Server::processClientRequest(int clientSocket, Request &request, RequestValidator &validator)
{
	std::cout << "Reading client request" << std::endl;			
	std::cout << "ANTES DO createParsedMessage "  << std::endl;



	request = Request().createParsedMessage(clientSocket);

	std::cout << request.getMensageRequest() << std::string(42, '-') << '\n' << std::endl;
		std::cout << "DEPOIS DO createParsedMessage "  << std::endl;
	std::string cgi = "/cgi-bin";
	
	if (!this->conf.getLocation(request.getPortNumber(), cgi).empty())
	{
		if (Utils::endsWith(request.getPath() , ".py")) 
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
	int i = 0;
    for (std::map<time_t, int>::iterator it = clienstSocks.begin(); it != clienstSocks.end(); ++it)
    {

        std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa " << std::endl;
        RequestValidator requestValidator;
        Request request;
		 	checkTimeout();
        int clientSocket = it->second; // Obtém o socket do cliente do mapa
        if (FD_ISSET(clientSocket, &this->readSocket))
        {
            processClientRequest(clientSocket, request, requestValidator);
        }
        if (FD_ISSET(clientSocket, &writeSocket))
        {
            sendClientResponse(clientSocket, i, request, requestValidator);
        }
		i++;

    }
}
void Server::acceptNewClient(int sockfd)
{
	sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	
	int clientSocket = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);

	if (clientSocket == -1)
	{
		close(clientSocket);
		std::cout << "Failed to accept new client" << std::endl;
		return ;
	}
	FD_SET(clientSocket, &this->readSocket);
	_last_msg_time = time(NULL);
	this->clienstSocks[_last_msg_time] = clientSocket;
}


void Server::closeConnection(const int &i)
{
	close(i);
	this->clienstSocks.erase(i);
}

void Server::checkTimeout()
{
    for (std::map<time_t, int>::iterator it = clienstSocks.begin(); it != clienstSocks.end(); it++)
    {
        if (time(NULL) -  it->first > CONNECTION_TIMEOUT)
        {
            std::cout << "Failed to check timeout " << time(NULL) -  it->first<< std::endl;
			close(it->second);
            clienstSocks.erase(it);
        }
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
			std::cout << "Select failed" << std::endl;
			break;
		}

		handleNewClients();

		processClients();

	}

	closeSockets();
	this->conf.deleteConfParser();
}

Server::Server(Conf &config) : conf(config), clienstSocks()
{
	Socket socket(conf.getServersData());
	if(!socket.succeed())
		return;
	runServer(socket);
}

bool Server::gSignalInterrupted = false;
