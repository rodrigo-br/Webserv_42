#ifndef RESPONSE_H
# define RESPONSE_H

# include <cstring>
# include "classes/ResponseBuilder.hpp"
# include <stdlib.h>

class Response
{
    private:
        ResponseBuilder builder;
        const char      *response;
        size_t          size;

    public:
        Response();
        ~Response();

        const char      *get_response() const;
        size_t          get_size() const;
};

#endif
