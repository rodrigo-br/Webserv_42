#include "classes/ValidConfigurations.hpp"

ValidConfigurations::ValidConfigurations()
{
    this->_serverConfigurations["listen"] = new ValidateFunction<std::string>("na chuva");
    (*this->_serverConfigurations["listen"])("Cavalinho");
    // this->_serverConfigurations["root"] = ;
    // this->_serverConfigurations["location"] = ;
    // this->_locationConfigurations["http_methods"] = ;
    // this->_locationConfigurations["index"] = ;
    // this->_locationConfigurations["directory_listing"] = ;
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

