#include "classes/RequestParser.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>

RequestParser::RequestParser(void) : _method(HttpMethodEnum::UNKNOWN) {}

RequestParser::~RequestParser(void) {}

void    RequestParser::parser_http_request(char *request) 
{
	std::string url, temp, httpVersion, strRequest;

	//START_LINE
	strRequest = request;
	std::istringstream iss(strRequest);
	std::string line;
	if (std::getline(iss, line)) {
		iss.str(line);
		iss >> this->str_method >> this->_path >> this->_http_version;
	}

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

