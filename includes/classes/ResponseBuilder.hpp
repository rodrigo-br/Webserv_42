#ifndef RESPONSE_BUILDER_H
# define RESPONSE_BUILDER_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <iostream>
# include <cstring>
# include <stdlib.h>

class ResponseBuilder
{
    public:
        const char  *build_response();

    private:
        ContentTypes contentTypes;
        StatusCodes statusCodes;

        std::string get_protocol_version() const;
        std::string get_status_code() const;
        std::string get_status_msg() const;
        std::string get_content_type() const;
};

#endif
