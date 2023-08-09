#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>

class RequestParser
{

	public:
		RequestParser ();
		~RequestParser();

		void    							parser_http_request(char *request);
		std::string 						get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_http_version(void) const;
		std::string							get_body(void) const;
		std::string							get_header(std::string header_name) const;
		void								set_path(std::string new_path);

	private:
		void 								_parse_request_start_line( std::string &line, std::istringstream &iss );
		void 								_parse_request_header( std::string &line, std::istringstream &iss );
		void 								_parse_request_bory( std::string &line, std::istringstream &iss );

    	std::map<std::string, std::string> 	_headers;
		std::string  						_method;
		std::string                 		_path;
		std::string                			_http_version;
		std::string							_requestBody;
		std::string							_port;
};

#endif
