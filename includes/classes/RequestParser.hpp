#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <string>
#include "enums/HttpMethodsEnum.hpp"
#include <iostream>

class RequestParser
{
    private:
        HttpMethodEnum::httpMethod  _method;
        std::string                 _line;

    public:
        RequestParser(std::string request);
        HttpMethodEnum::httpMethod get_method();

};

#endif
