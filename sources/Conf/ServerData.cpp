#include "classes/ServerData.hpp"

ServerData::ServerData()
{
    this->_root = "wwwroot";
    this->_location["/"] = Location("index.html");
    this->_location["/api"] = Location("api.html");
    this->_location["/api/upload"] = Location("upload.html");
    this->_location["/images"] = Location("images.html");
    this->_location["/images/random"] = Location("index.html");
}

std::string ServerData::getRoot() const
{
    return this->_root;
}

std::map<std::string, Location> ServerData::getLocations() const
{
    return this->_location;
}

std::string ServerData::getLocation(std::string location_name) const
{
    std::map<std::string, Location>::const_iterator it = this->_location.find(location_name);

    if (it != this->_location.end())
        return it->second.getIndex();
    else
        return  "";
}
