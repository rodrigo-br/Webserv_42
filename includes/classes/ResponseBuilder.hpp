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

class ResponseBuilder
{
    public:
        IMethod *method;

        ResponseBuilder();
        ~ResponseBuilder();
        const char  *build_response();
        const char  *build_body();
        ssize_t     get_body_size() const;
        bool        has_body() const;
};

#endif
