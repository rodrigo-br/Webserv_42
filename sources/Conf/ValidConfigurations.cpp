#include "interfaces/ValidateInterface/ValidConfigurations.hpp"

ValidConfigurations::ValidConfigurations()
{
    int unsafePortsAsInt[] = {1719,1720,1723,2049,3659,4045,5060,5061,6000,6566,6665,6666,6667,6668,6669,6697,10080};
    const size_t numberOfPorts = sizeof(unsafePortsAsInt)/sizeof(unsafePortsAsInt[0]);
    this->_serverConfigurations["listen"] = new ValidatePortIsSafe<numberOfPorts>(unsafePortsAsInt);
    this->_serverConfigurations["root"] = new ValidateDirectoryExist();
    // this->_serverConfigurations["location"] = new ValidateLocation<>();
    // this->_locationConfigurations["http_methods"] = new ValidateMethods<>();
    // this->_locationConfigurations["index"] = new ValidateLocationIndex<>();
    // this->_locationConfigurations["directory_listing"] = new ValidateDirectoryListing<>();
}

ValidConfigurations::~ValidConfigurations()
{
    for (std::map<std::string, IValidateFunction*>::iterator it = this->_serverConfigurations.begin();
        it != this->_serverConfigurations.end(); ++it)
    {
        delete it->second;
    }
}

bool ValidConfigurations::ValidateAServerConfiguration(std::string &key, std::string &value)
{
    std::map<std::string, IValidateFunction*>::iterator it = this->_serverConfigurations.find(key);
    if (it != this->_serverConfigurations.end())
    {
        if (it->second != NULL)
        {
            return (*(it->second))(value);
        }
    }
    return false;
}

/*
server {
    listen 8000
    root wwwroot

    location / {
        http_methods 4
        index index.html
    }

    location /api {
        index api.html
    }

    location api/upload {
        http_methods 7
        index upload.html
    }

    location /images {
        index images.html
    }

    location /images/random {
        directory_listing on
        index index.html
    }
}

server {
    listen 4000
    root wwwroot

    location / {
        http_methods 4
        index index.html
    }

    location api/upload {
        http_methods 4
        index upload.html
    }
}*/
