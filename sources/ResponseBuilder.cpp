#include "classes/ResponseBuilder.hpp"
#include <iostream>
#include <cstring>
#include <stdlib.h>

const char *ResponseBuilder::build_response()
{
    std::string response;

    // Opening Line
    response.append(this->get_protocol_version());
    response.append(this->get_status_code());
    response.append(this->get_status_msg());
    response.append("\n");

    // Headers
    response.append("Content-Type: ");
    response.append(this->get_content_type());
    response.append("\n\n");

    // convert string to char ptr
    char *teste = (char *)calloc(1, response.length() + 1);
    std::strcpy(teste, response.c_str());

    return teste;
}

std::string ResponseBuilder::get_protocol_version() const
{
    return "HTTP/1.1 ";
}

std::string ResponseBuilder::get_status_code() const
{
    return "200 ";
}

std::string ResponseBuilder::get_status_msg() const
{
    return "OK";
}

std::string ResponseBuilder::get_content_type() const
{
    return contentTypes.get_mime_type(".png");
}

