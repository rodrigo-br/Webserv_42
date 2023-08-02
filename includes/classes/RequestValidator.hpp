#ifndef REQUEST_VALIDATOR_HPP
#define REQUEST_VALIDATOR_HPP

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>

class RequestValidator
{

	public:
		RequestValidator ();
		~RequestValidator();
		

		void    					parser_http_request(char *request);
		HttpMethodEnum::httpMethod	get_method(void) const;
		bool				        get_path(void) const;
		bool				        get_http_version(void) const;
		bool				        get_user_agent(void) const;
		bool				        get_host(void) const;
		bool				        get_body(void) const;
		bool				        get_header(std::string header_name) const;


		HttpMethodEnum::httpMethod      _method;
		bool                 		    _path;
		bool                			_http_version;
		bool							_requestBody;
};

#endif
