
#include "classes/Socket.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

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

bool  Socket::createSockaddr(int port)
{
    _sockaddr.sin_family = AF_INET;
    _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _sockaddr.sin_port = htons(port);
    return (false);
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


bool bindSocket(int socketFd, const sockaddr_in& sockaddr) 
{
    if (Utils::check(bind(socketFd, (const struct sockaddr*)&sockaddr, sizeof(sockaddr)), "Bind")) 
    {
        close(socketFd);
        return true;
    }
    return false;
}

bool listenOnSocket(int socketFd) 
{
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

bool Socket::initializeSockets(std::map<int, ServerData>& conf) 
{

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
        if (createSockaddr(port))
        {
            return false;
        }

        if (bindSocket(serverSocket, _sockaddr)) 
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