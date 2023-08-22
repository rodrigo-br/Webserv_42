#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>
# include <cstdlib>
// # include <sstream>
# include <string>
# include <typeinfo>
# include <vector>

class RequestParser
{

	public:
		RequestParser ();
		~RequestParser();

		void    							parserHttpRequest(char *request);
		std::string 						getMethod(void) const;
		std::string							getPath(void) const;
		std::string							getHttpVersion(void) const;
		std::string							getBody(void) const;
		std::string							getHeader(std::string headerName) const;
		std::string							getPort(void) const;
		std::string							getQuery(void) const;
		std::string							getFileExec(void) const;
		int									getPortNumber(void) const;
		void								setPath(std::string newPath);
		void								setBody(std::string newBody);
		void								setFileExec(std::string newFileExec);


	private:
		void								parseRequestPort(void);
		void  								parseRquestQuery();
		void 								parseRequestStartLine(std::string &line, std::istringstream &iss);
		void 								parseRequestHeader(std::string &line, std::istringstream &iss);
		void 								parseRequestBody(std::string &line, std::istringstream &iss);
		// void								parserRequestFileExec;
    	std::map<std::string, std::string> 	_headers;
		std::string  						_method;
		std::string                 		_path;
		std::string                			_httpVersion;
		std::string							_requestBody;
		std::string							_port;
		int									_portNumber;
		std::string							_query;
		std::string							_fileExec;

};

#endif
