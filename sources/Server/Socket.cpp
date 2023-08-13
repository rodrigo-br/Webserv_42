
#include "classes/Socket.hpp"

Socket::Socket(std::map<int, ServerData>& conf)
{
    this->_succeed = initializeSockets(conf);
}

fd_set Socket::getReadFds()
{
    return this->_readFds;
}

fd_set Socket::getWriteFds()
{
    return this->_writeFds;
}

bool Socket::succeed()
{
    return _succeed;
}

static sockaddr_in createSockaddr(int port)
{
	sockaddr_in _sockaddr;
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(port);
	return (_sockaddr);
}


bool createAndConfigureSocket(int& socketFd, int optval) 
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (Utils::check(socketFd, "Create Socket")) 
    {
        return true;
    }

    if (Utils::check(setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)), "Socket Reusable")) 
    {
        close(socketFd);
        return true;
    }

    return false;
}


bool bindSocket(int socketFd, const sockaddr_in& sockaddr) {
    if (Utils::check(bind(socketFd, (const struct sockaddr*)&sockaddr, sizeof(sockaddr)), "Bind")) 
    {
        close(socketFd);
        return true;
    }
    return false;
}

bool listenOnSocket(int socketFd) {
    if (Utils::check(listen(socketFd, 10), "Listen")) 
    {
        close(socketFd);
        return true;
    }
    return false;
}

bool setNonBlocking(int socketFd) {
    if (Utils::check(fcntl(socketFd, F_SETFL, O_NONBLOCK), "FCNTL")) 
    {
        close(socketFd);
        return true;
    }
    return false;
}

std::vector<int>  Socket::getlistenSockets()
{
    return this->_listenSockets;
}

bool Socket::initializeSockets(std::map<int, ServerData>& conf) {

	FD_ZERO(&this->_readFds);
    FD_ZERO(&this->_writeFds);
    for (std::map<int, ServerData>::const_iterator it = conf.begin(); it != conf.end(); ++it) 
    {
        int port = it->first;
        int optval = 1;
        int serverSocket;

        if (createAndConfigureSocket(serverSocket, optval)) 
        {
            return false;
        }

        sockaddr_in sockaddr = createSockaddr(port);

        if (bindSocket(serverSocket, sockaddr)) 
        {
            return false;
        }

        if (listenOnSocket(serverSocket)) 
        {
            return false;
        }

        if (setNonBlocking(serverSocket)) 
        {
            return false;
        }

        FD_SET(serverSocket, &this->_readFds);
        this->_listenSockets.push_back(serverSocket);
    }
    return true;
}