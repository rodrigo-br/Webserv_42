#include "classes/Conf.hpp"
#include <iostream>

Conf::Conf(ConfParser *parser) : _parser(parser)
{
    this->_listen = 8000;
    this->_root = "wwwroot";
    this->_location["/"] = Location("index.html");
    this->_location["/api"] = Location("api.html");
    this->_location["/api/upload"] = Location("upload.html");
    this->_location["/images"] = Location("images.html");
    this->_location["/images/random"] = Location("index.html");
}

bool Conf::succeeded()
{
    return true;
}

void Conf::deleteConfParser()
{
    delete this->_parser;
}

int Conf::get_listen() const
{
    return this->_listen;
}

std::string Conf::get_root() const
{
    return this->_root;
}

std::map<std::string, Location> Conf::get_locations() const
{
    return this->_location;
}

std::string Conf::get_locations(std::string location_name) const
{
    std::map<std::string, Location>::const_iterator it = this->_location.find(location_name);

    if (it != this->_location.end())
        return it->second.get_index();
    else
        return  "";
}
