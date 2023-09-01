#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>
# include <cstdlib>
// # include <sstream>
#include <cstring>
#include <sys/socket.h>
# include <string>
# include <typeinfo>
# include <vector>

#define CRLF			"\r\n"
#define CRLF_DOUBLE		"\r\n\r\n"
#define FILENAME_ID		"filename=\""
#define DOUBLE_QUOTE	"\""
#define BUFFER_SIZE		20

class RequestParser
{

	public:
		RequestParser ();
		~RequestParser();

		void    							parserHttpRequest(int fdConection);
		std::string 						getMethod(void) const;
		std::string							getPath(void) const;
		std::string							getHttpVersion(void) const;
		std::string							getBody(void) const;
		std::string							getHeader(std::string headerName) const;
		std::string							getPort(void) const;
		std::string							getServerName(void) const;
		std::string							getQuery(void) const;
		std::string							getFileExec(void) const;
		std::string							getFileName(void) const;
		std::string							getRequest(void) const;

		int									getPortNumber(void) const;
		void								setPath(std::string newPath);
		void								setBody(std::string newBody);
		void								setFileExec(std::string newFileExec);


	private:
		void								parseRequestPort();
		void								parserServerName();
		void  								parseRquestQuery();
		void 								parseRequestStartLine(std::string &line, std::istringstream &iss);
		void 								parseRequestHeader(std::string &line, std::istringstream &iss);
		// void 								parseRequestBody(std::string &line, std::istringstream &iss);
				void 								parseRequestBody(int fdConection);


void _clean_header(std::string &temp_line);
void _clean_footer(std::string &temp_line);

		void								parseMultipartFormDataBody(const std::string& boundary);
		int								parseContentLengthBody(std::istringstream& iss);
		void 								parseChunkedBody(std::istringstream& iss);
		int									getContentLength() const;
		void       							setFileName();
void setFileName(std::istringstream& iss);

void parseMultipartFormDataBody(const std::string& boundary, std::istringstream& iss);

    	std::map<std::string, std::string> 	_headers;
		std::string  						_method;
		std::string                 		_path;
		std::string                			_httpVersion;
		std::string							_requestBody;
		std::string							_port;
		int									_portNumber;
		std::string							_query;
		std::string							_fileExec;
		std::string							_serverName;
		std::string							_fileName;
		int									_fdClient;
		std::string							_request;


};

#endif
