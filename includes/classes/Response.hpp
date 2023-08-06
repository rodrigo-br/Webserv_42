#ifndef RESPONSE_H
# define RESPONSE_H

# include <cstring>
# include "classes/ResponseBuilder.hpp"
# include <stdlib.h>
# include "classes/Request.hpp"
# include "classes/RequestValidator.hpp"

class Response
{
    private:
        ResponseBuilder *_builder;
        const char      *_response;
        const char      *_body;
        size_t          _size;

    public:
        Response(ResponseBuilder *builder);
        ~Response();

        bool            has_body() const;
        ssize_t         body_size() const;
        const char      *get_body();
        const char      *get_response() const;
        size_t          get_size() const;
};

#endif
