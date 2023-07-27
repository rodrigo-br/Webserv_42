#ifndef RESPONSE_BUILDER_H
# define RESPONSE_BUILDER_H

# include <string>

class ResponseBuilder
{
    public:
        const char  *build_response();

        std::string get_protocol_version() const;
        std::string get_status_code() const;
        std::string get_status_msg() const;
        std::string get_content_type() const;
};

#endif
