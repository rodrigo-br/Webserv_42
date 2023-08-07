#include "classes/Conf.hpp"
#include <iostream>

Conf::Conf()
{
    this->listen = 8000;
    this->root = "wwwroot/";
    this->location["/"] = Location("index.html");
    this->location["/api/"] = Location("api.html");
    this->location["/api/upload/"] = Location("upload.html");
    this->location["/images/"] = Location("images.html");
    this->location["/images/random/"] = Location("index.html");
}

int Conf::get_listen() const
{
    return this->listen;
}

std::string Conf::get_root() const
{
    return this->root;
}

std::map<std::string, Location> Conf::get_locations() const
{
    return this->location;
}

std::string Conf::get_locations(std::string location_name) const
{
    std::map<std::string, Location>::const_iterator it = this->location.find(location_name);

    if (it != this->location.end())
        return it->second.get_index();
    else
        return  "";
}
