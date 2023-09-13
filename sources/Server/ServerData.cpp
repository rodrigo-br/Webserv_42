#include "classes/ServerData.hpp"

ServerData::ServerData()
{
    this->_errorPages[404] = "/statusCodes/404.html";
    this->_errorPages[405] = "/statusCodes/405.html";
    this->_errorPages[413] = "/statusCodes/413.html";
    this->_errorPages[500] = "/statusCodes/500.html";
    this->_errorPages[501] = "/statusCodes/501.html";
    this->_serverNames.push_back("localhost");
    this->_root = "wwwroot";
    this->_bodySizeLimit = 5000000;
    this->_configurations["root"] = &ServerData::setRoot;
    this->_configurations["index"] = &ServerData::setLocationIndex;
    this->_configurations["directory_listing"] = &ServerData::setLocationDirectoryListening;
    this->_configurations["http_methods"] = &ServerData::setLocationAllowedMethods;
    this->_configurations["server_names"] = &ServerData::setServerNames;
    this->_configurations["body_size_limit"] = &ServerData::setBodySizeLimit;
}

std::vector<std::string> ServerData::getServerNames() const
{
    return this->_serverNames;
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

void ServerData::setServerNames(std::string name)
{
    this->_serverNames.push_back(name);
}

int ServerData::getBodySizeLimit() const
{
    return this->_bodySizeLimit;
}

void ServerData::setBodySizeLimit(std::string value)
{
    this->_bodySizeLimit = std::atoi(value.c_str());
}

bool ServerData::isDirectoryListingLocation(std::string locationPath)
{
    std::map<std::string, Location>::const_iterator it = this->_location.find(locationPath);

    if (it != this->_location.end())
    {
        return it->second.getDirectoryListening();
    }
    return false;
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
        this->_currentLocation = tokens[1];
        this->setLocation(tokens[1], Location());
        return ;
    }
    int erro = std::atoi(tokens[0].c_str());
    if (erro >= 400 && erro < 600)
    {
        this->setErrorPage(erro, tokens[1]);
        return ;
    }

    std::map<std::string, void (ServerData::*)(std::string)>::iterator it = _configurations.find(tokens[0]);
    if (it != _configurations.end())
    {
        (this->*(it->second))(tokens[1]);
    }
}

void ServerData::setLocationIndex(std::string index)
{
    this->_location[this->_currentLocation].setIndex(index);
}

void ServerData::setLocationAllowedMethods(std::string allowedMethods)
{
    this->_location[this->_currentLocation].setAllowedMethods(std::atoi(allowedMethods.c_str()));
}

void ServerData::setLocationDirectoryListening(std::string directoryListening)
{
    this->_location[this->_currentLocation].setDirectoryListening((directoryListening.compare("on") == 0));
}

void ServerData::setErrorPage(int erro, std::string errorPagePath)
{
    this->_errorPages[erro] = errorPagePath;
}

int ServerData::getAllowed(std::string locationPath)
{
    std::map<std::string, Location>::iterator it = this->_location.find(locationPath);
    if (it != this->_location.end())
    {
        int allowed = it->second.getAllowedMethods();
        return ((allowed <= 8 && allowed > 0) ? allowed : 1);
    }
    return 0;
}
std::map<int, std::string> ServerData::getErrorPages()
{
    return this->_errorPages;
}

