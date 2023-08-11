#include "classes/RequestParser.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

RequestParser::RequestParser(void) : _headers(), _method(""), _path(""), _httpVersion(""), _requestBody("") { }

RequestParser::~RequestParser(void) {}

void    RequestParser::parserHttpRequest(char *request)
{
	std::string			line;
	std::istringstream	iss(request);

	_parseRequestStartLine(line, iss);
	_parseRequestHeader(line, iss);
	_parseRequestBody(line, iss);
}

void RequestParser::_parseRequestBody(std::string& line, std::istringstream& iss)
{
    while (std::getline(iss, line)) {
        this->_requestBody += line;
    }
}

void 	RequestParser::_parseRequestHeader( std::string &line, std::istringstream &iss )
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

void	RequestParser::_parseRequestStartLine(std::string &line, std::istringstream &iss)
{
	if (std::getline(iss, line))
	{
        std::istringstream lineStream(line);
        lineStream >> this->_method >> _path >> this->_httpVersion;
    }
}

std::string RequestParser::getMethod(void) const
{
    return this->_method;
}

std::string RequestParser::getPath(void) const
{
    return this->_path;
}

std::string RequestParser::getHttpVersion(void) const
{
    return this->_httpVersion;
}

std::string RequestParser::getBody(void) const
{
    return this->_requestBody;
}

std::string RequestParser::getHeader(std::string headerName) const
{
    std::map<std::string, std::string>::const_iterator it = this->_headers.find(headerName);

    if (it != this->_headers.end())
        return it->second;
    else
        return "";
}

void RequestParser::setPath(std::string newPath)
{
    this->_path = newPath;
}

