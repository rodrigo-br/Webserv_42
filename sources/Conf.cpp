#include "classes/Conf.hpp"

Conf::Conf() : listen(8000), root("files/")
{
    location["/"] = "index.html";
};

int Conf::get_listen() const
{
    return this->listen;
}

std::string Conf::get_root() const
{
    return this->root;
}

std::map<std::string, std::string> Conf::get_locations() const
{
    return this->location;
}

std::string Conf::get_locations(std::string location_name) const
{
    std::map<std::string, std::string>::const_iterator it = this->location.find(location_name);

    if (it != this->location.end())
        return it->second;
    else
        return  "";
}
