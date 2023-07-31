#include "classes/RequestParser.hpp"

RequestParser::RequestParser(std::string request) : _line(request)
{

}

HttpMethodEnum::httpMethod RequestParser::get_method()
{
    _line = _line.substr(4);
    _method = HttpMethodEnum::GET;
    return _method;
}
