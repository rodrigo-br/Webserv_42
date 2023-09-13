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
# include "classes/Location.hpp"

# define BUFFER_SIZE2 30000

class Request
{
	public:

		Request();
		~Request();

		Request						&createParsedMessage(int &fdConnecion, bool &errorRead);
		std::string	        		getMensageRequest() const;
		std::string					getMethod() const;
		std::string					getPath(void) const;
		std::string					getHttpVersion(void) const;
		std::string					getBody(void) const;
		std::string					getHeader(std::string headerName) const;
		std::string					getServerName(void) const;
		std::string					getPort(void) const;
		std::string					getFileName(void) const;
		int							getPortNumber(void) const;
		void        				setPath(std::string newPath);
		std::string 				getQuery(void) const;
		std::string					getFileExec(void) const;
		void						setFileExec(std::string fileExec);
		void						setBody(std::string newBody);
		void						buildCGI(void);
		void						setAllowed(int value);
		int							getAllowed();
		void						setMethod(std::string method);
		int 						getContentLength() const;

	private:
		RequestParser				_parser;
		char            			_request[BUFFER_SIZE2];
		int							_allowed;

};

#endif
