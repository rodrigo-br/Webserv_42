#include "classes/RequestParser.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

RequestParser::RequestParser(void) : 
 _str_method(""),_headers(), _method(HttpMethodEnum::UNKNOWN), _path(""), _http_version(""), _requestBody("") { }

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
        if (line == "\r" || line == "\r\n") 
                break;
        else
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                size_t lastNonCRLF = line.find_last_not_of("\r\n");
                if (lastNonCRLF != std::string::npos) {
                    line = line.substr(0, lastNonCRLF + 1);
                    std::string headerName = line.substr(0, colonPos);
                    std::string headerValue = line.substr(colonPos + 2);
                    this->_headers[headerName] = headerValue;
                }
            }
        }
	}
}

void	RequestParser::_parse_request_start_line(std::string &line, std::istringstream &iss)
{

	if (std::getline(iss, line)) 
	{
        std::istringstream lineStream(line);
        lineStream >> this->_str_method >> this->_path >> this->_http_version;
    }
	set_method();
}

HttpMethodEnum::httpMethod RequestParser::set_method()
{
	if (this->_str_method.compare("GET") == 0)
		_method = HttpMethodEnum::GET;
	else if (this->_str_method.compare("POST") == 0)
		_method = HttpMethodEnum::POST;
	else if (this->_str_method.compare("DELETE") == 0)
		_method = HttpMethodEnum::DELETE;
	return _method;
}

HttpMethodEnum::httpMethod RequestParser::get_method(void) const
{
    return this->_method;
}

std::string RequestParser::get_path(void) const
{
    return this->_path;
}

std::string RequestParser::get_http_version(void) const
{
    return this->_http_version;
}

std::string RequestParser::get_body(void) const
{
    return this->_requestBody;
}

std::string RequestParser::get_header(std::string header_name) const
{
    std::map<std::string, std::string>::const_iterator it = this->_headers.find(header_name);

    if (it != this->_headers.end())
        return it->second;
    else
        return "";
}
