#ifndef RESPONSE_BUILDER_H
# define RESPONSE_BUILDER_H

# include <string>
# include "classes/ContentTypes.hpp"

class ResponseBuilder
{
    public:
        const char  *build_response();
        ContentTypes contentTypes;

        std::string get_protocol_version() const;
        std::string get_status_code() const;
        std::string get_status_msg() const;
        std::string get_content_type() const;
};

#endif
