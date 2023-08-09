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

        bool            hasBody() const;
        ssize_t         bodySize() const;
        const char      *getBody();
        const char      *getResponse() const;
        size_t          getSize() const;
};

#endif
