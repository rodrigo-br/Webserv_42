#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <string>
#include "enums/HttpMethodsEnum.hpp"
#include <iostream>

class RequestParser
{

	public:
		RequestParser ();
		~RequestParser();
		
		void    parser_http_request(char *request);
		HttpMethodEnum::httpMethod set_method();

	private:
		std::string                 str_method;
		HttpMethodEnum::httpMethod  _method;
		std::string                 _path;
		std::string                 _http_version;
		std::string                 _user_agent;
};

#endif
