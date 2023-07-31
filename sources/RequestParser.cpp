#include "classes/RequestParser.hpp"

RequestParser::RequestParser(std::string request) : _line(request)
{
    _method = get_method();
}

HttpMethodEnum::httpMethod RequestParser::get_method()
{
    _line = _line.substr(4);
    std::cout << _line << std::endl;
    return HttpMethodEnum::GET;
}
