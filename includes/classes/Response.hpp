#ifndef RESPONSE_H
# define RESPONSE_H

# include <cstring>
# include "classes/ResponseBuilder.hpp"
# include <stdlib.h>

class Response
{
    public:
        ResponseBuilder builder;
        const char      *response;
        size_t          size;

        Response();
        ~Response();

        const char      *get_response() const;
        size_t          get_size() const;
};

#endif
