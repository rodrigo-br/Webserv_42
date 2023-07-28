#ifndef REQUEST_H
# define REQUEST_H

# include <cstring>
# include <stdlib.h>
# include <iostream> // For cout
# include "enums/HttpMethodsEnum.hpp"
# include <unistd.h> // For read
#include <cerrno>

# define BUFFER_SIZE 30000

class Request
{
    public:
        
        int              _metodo;
        bool             _url;
        bool             _http_version;
        std::string      _contentLength;
        std::string      _transferEncoding;
        std::string      _host;
        std::string      _contentType;
        std::string      _userAgent;


        char             _request[BUFFER_SIZE];

        // GET / HTTP/1.1
// Host: localhost:8000
// User-Agent: curl/7.81.0
// Accept: */
        Request( int fd_connection );
        ~Request();

        bool check(ssize_t result, int erro = -1);

        const char*         get_request() const;
        size_t              get_size() const;
};

#endif
