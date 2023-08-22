#ifndef REQUEST_H
# define REQUEST_H

# include <cstring>
# include <stdlib.h>
# include <iostream>
# include <unistd.h>
# include <cerrno>
# include "classes/Utils.hpp"
# include "classes/RequestParser.hpp"
# include "enums/HttpMethodsEnum.hpp"

# define BUFFER_SIZE 30000

class Request
{
	public:

		Request();
		~Request();

		Request						&createParsedMessage(int fdConnecion);
		const char*         		getMensageRequest() const;
		std::string					getMethod() const;
		std::string					getPath(void) const;
		std::string					getHttpVersion(void) const;
		std::string					getBody(void) const;
		std::string					getHeader(std::string headerName) const;
		std::string					getPort(void) const;
		int							getPortNumber(void) const;
		void        				setPath(std::string newPath);
		std::string 				getQuery(void) const;
		std::string					getFileExec(void) const;
		void						setFileExec(std::string fileExec);
		void						setBody(std::string newBody);
		void						buildCGI(void);

	private:
		RequestParser				_parser;
		char            			_request[BUFFER_SIZE];

};

#endif
