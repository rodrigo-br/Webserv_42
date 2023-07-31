#include "classes/Conf.hpp"

Conf::Conf() : listen(8000), root("/")
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

