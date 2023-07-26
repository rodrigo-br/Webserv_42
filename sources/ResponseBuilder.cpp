#include "classes/ResponseBuilder.hpp"
#include <iostream>
#include <cstring>
#include <stdlib.h>

const char *ResponseBuilder::build_response()
{
    std::string response = "HTTP/1.1 200 OK\nContent-Type: image/png\n\n";

    char *teste = (char *)calloc(1, response.length() + 1);
    std::strcpy(teste, response.c_str());

    return teste;
}
