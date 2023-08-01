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
	std::string			line;
	std::istringstream	iss(request);

	_parse_request_start_line(line, iss);
	_parse_request_header(line, iss);
	_parse_request_bory(line, iss);
}

void RequestParser::_parse_request_bory(std::string& line, std::istringstream& iss)
{
    while (std::getline(iss, line)) {
        _requestBody += line;
	}
}

void 	RequestParser::_parse_request_header( std::string &line, std::istringstream &iss )
{
	while (std::getline(iss, line) && !line.empty())
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
}




void	RequestParser::_parse_request_start_line(std::string &line, std::istringstream &iss)
{

	if (std::getline(iss, line)) 
	{
        std::istringstream lineStream(line);
        lineStream >> this->str_method >> this->_path >> this->_http_version;
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

std::string RequestParser::get_bory(void)
{
    return this->_requestBody;
}
