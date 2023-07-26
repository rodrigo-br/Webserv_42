#ifndef RESPONSE_H
# define RESPONSE_H

# include <string>

class Response
{
    public:
        std::string response;
        size_t      size;

        Response();

        void build_response();
        std::string get_response() const;
        size_t get_size() const;
};

#endif
