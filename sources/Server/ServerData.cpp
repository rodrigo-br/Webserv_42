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

void ServerData::setRoot(std::string root)
{
    this->_root = root;
}

void ServerData::setLocation(std::string path, Location location)
{
    this->_location[path] = location;
}

std::string ServerData::getLocation(std::string locationName) const
{
    std::map<std::string, Location>::const_iterator it = this->_location.find(locationName);

    if (it != this->_location.end())
        return it->second.getIndex();
    else
        return  "";
}

void ServerData::setConfiguration(std::vector<std::string> tokens)
{
    if (tokens[0].compare("location") == 0)
    {
        setLocation(tokens[1], Location());
    }
    else if (tokens[0].compare("root") == 0)
    {
        setRoot(tokens[1]);
    }
}
