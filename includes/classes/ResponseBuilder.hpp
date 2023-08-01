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

class ResponseBuilder
{
    public:
        const char  *build_response();
        const char  *get_body();
        ssize_t     get_body_size() const;
        bool        has_body() const;

    private:
        ContentTypes contentTypes;
        StatusCodes statusCodes;
        bool        hasBody;
        ssize_t     body_size;

        std::string build_start_line() const;
        std::string build_headers() const;
        char *BODY_BUILDER_BIIIIHHHHLLL();
        std::string get_protocol_version() const;
        std::string get_status_code() const;
        std::string get_status_msg() const;
        std::string get_content_type() const;
};

#endif
