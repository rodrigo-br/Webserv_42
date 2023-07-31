#ifndef REQUEST_H
# define REQUEST_H

# include <cstring>
# include <stdlib.h>
# include <iostream>
# include "enums/HttpMethodsEnum.hpp"
# include <unistd.h>
# include <cerrno>
# include "classes/Utils.hpp"

# define BUFFER_SIZE 30000

class Request
{
    public:

        int              _method;
        bool             _url;
        bool             _http_version;
        std::string      _contentLength;
        std::string      _transferEncoding;
        std::string      _host;
        std::string      _contentType;
        std::string      _userAgent;


        char             _request[BUFFER_SIZE];

        Request( int fd_connection );
        ~Request();

        const char*         get_request() const;
        size_t              get_size() const;
};

#endif
