#ifndef RESPONSE_BUILDER_H
# define RESPONSE_BUILDER_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <fstream>
# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include "interfaces/MethodCreator.hpp"
# include "classes/Request.hpp"
# include "classes/RequestValidator.hpp"

class ResponseBuilder
{
    private:
        IMethod *_method;

    public:

        ResponseBuilder(Request &, RequestValidator &);
        ~ResponseBuilder();
        const char  *build_response();
        const char  *build_body();
        ssize_t     get_body_size() const;
        bool        has_body() const;
};

#endif
