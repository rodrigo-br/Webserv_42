#include "classes/Conf.hpp"
#include <iostream>

Conf::Conf(ConfParser *parser) : _parser(parser)
{
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
    return this->_parser->getRoot(port);
}

std::map<std::string, Location> Conf::getLocations(int port) const
{
    return this->_parser->getLocations(port);
}

std::map<int, ServerData>& Conf::getServersData()
{
    return this->_parser->getServersData();
}


bool Conf::criticalError()
{
    return this->_parser->getCriticalError();
}

std::string Conf::getLocation(int port, std::string locationName) const
{
    return this->_parser->getLocation(port, locationName);
}
