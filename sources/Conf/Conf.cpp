#include "classes/Conf.hpp"
#include <iostream>

Conf::Conf(ConfParser *parser) : _parser(parser)
{
    this->_serversData[8000] = ServerData();
    this->_serversData[8080] = ServerData();
    this->_serversData[65535] = ServerData();
    this->_serversData[65536] = ServerData();
    this->_serversData[1024] = ServerData();
    this->_serversData[6664] = ServerData();
    this->_serversData[6668] = ServerData();
    this->_serversData[56666] = ServerData();
}

bool Conf::succeeded()
{
    return true;
}

void Conf::deleteConfParser()
{
    delete this->_parser;
}

std::string Conf::getRoot(int port) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getRoot();
    else
        throw std::invalid_argument("Porta não encontrada");
}

std::map<std::string, Location> Conf::getLocations(int port) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getLocations();
    else
        throw std::invalid_argument("Porta não encontrada");
}


std::map<int, ServerData>& Conf::getServersData()
{
    return this->_serversData;
}

std::string Conf::getLocation(int port, std::string locationName) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getLocation(locationName);
    else
        throw std::invalid_argument("Porta não encontrada");
}
