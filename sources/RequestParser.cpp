#include "classes/RequestParser.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

RequestParser::RequestParser(void) : _method(HttpMethodEnum::UNKNOWN) {}

RequestParser::~RequestParser(void) {}

void    RequestParser::parser_http_request(char *request) 
{
	std::string			strRequest;
	strRequest = request;
	std::istringstream	iss(strRequest);
	std::string			line;

	if (std::getline(iss, line)) 
	{
        std::istringstream lineStream(line);
        lineStream >> this->str_method >> this->_path >> this->_http_version;
    }

	// header
	while (std::getline(iss, line))
	{
        size_t colonPos = line.find(':');
		size_t lastNonCRLF = line.find_last_not_of("\r\n");
		if (lastNonCRLF != std::string::npos) {
			line = line.substr(0, lastNonCRLF + 1);
		}
        if (colonPos != std::string::npos) {
            std::string headerName = line.substr(0, colonPos);
            if (headerName.compare("User-Agent") == 0) {
                this->_user_agent = line.substr(colonPos + 2);
            }
			if (headerName.compare("Host") == 0) {
                this->_host = line.substr(colonPos + 2);
            }
        }
    }
	set_method();
 }

HttpMethodEnum::httpMethod RequestParser::set_method()
{
	if (this->str_method.compare("GET") == 0)
		_method = HttpMethodEnum::GET;
	else if (this->str_method.compare("POST") == 0)
		_method = HttpMethodEnum::POST;
	else if (this->str_method.compare("DELETE") == 0)
		_method = HttpMethodEnum::DELETE;
	return _method;
}

HttpMethodEnum::httpMethod RequestParser::get_method(void)
{
    return this->_method;
}

std::string RequestParser::get_path(void)
{
    return this->_path;
}

std::string RequestParser::get_http_version(void)
{
    return this->_http_version;
}

std::string RequestParser::get_user_agent(void)
{
    return this->_user_agent;
}

std::string RequestParser::get_host(void)
{
    return this->_host;
}

