#include "classes/RequestValidator.hpp"

RequestValidator::RequestValidator(void)  { }

RequestValidator::~RequestValidator(void) {}

RequestValidator &RequestValidator::request_validator(Conf& conf, Request& request)
{
    if (request.get_body().empty())
        this->_requestBody = true;
    std::string locationResult = conf.get_locations(request.get_path());
    if (!locationResult.empty()) 
    {
    std::cout << locationResult << std::endl;
       this->_path = true;
    }
    if (request.get_http_version().compare("HTTP/1.1") == 0){
        this->_http_version = true;
    }
    return *this;
}

bool RequestValidator::get_path(void) const
{
    return _path;
}

bool RequestValidator::get_http_version(void) const
{
    return _http_version;
}

bool RequestValidator::get_body(void) const
{
    return _requestBody;
}
