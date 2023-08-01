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
		

		void    					parser_http_request(char *request);
		HttpMethodEnum::httpMethod	set_method();
		HttpMethodEnum::httpMethod	get_method(void);
		std::string					get_path(void);
		std::string					get_http_version(void);
		std::string					get_user_agent(void);
		std::string					get_host(void);
		std::string					get_bory(void);

	private:
		void 						_parse_request_start_line( std::string &line, std::istringstream &iss );
		void 						_parse_request_header( std::string &line, std::istringstream &iss );
		void 						_parse_request_bory( std::string &line, std::istringstream &iss );


		std::string                 str_method;
		HttpMethodEnum::httpMethod  _method;
		std::string                 _path;
		std::string                 _http_version;
		std::string                 _user_agent;
		std::string					_host;
		std::string					_requestBody;
};

#endif
