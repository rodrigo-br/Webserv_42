#include "classes/Request.hpp"
        
Request::Request( ) : _request() {	}

Request::~Request( void ) { }

std::string   Request::getMensageRequest( void ) const
{
    return (_parser.getRequest());
}

Request			&Request::createParsedMessage(int fdConnection)
{
	this->_parser.parserHttpRequest(fdConnection);
	return *this;
}

std::string Request::getMethod() const
{
    return this->_parser.getMethod();
}

std::string Request::getPath(void) const
{
    return this->_parser.getPath();
}

std::string Request::getServerName(void) const
{
    return this->_parser.getServerName();
}

std::string Request::getHttpVersion(void) const
{
    return this->_parser.getHttpVersion();
}

std::string Request::getBody(void) const
{
    return this->_parser.getBody();
}

std::string Request::getHeader(std::string headerName) const
{
    return this->_parser.getHeader(headerName);
}

std::string Request::getPort(void) const
{
    return this->_parser.getPort();
}

int Request::getPortNumber(void) const
{
    return  this->_parser.getPortNumber();
}

std::string Request::getQuery(void) const
{
    return this->_parser.getQuery();
}

std::string Request::getFileExec(void) const
{
    return  this->_parser.getFileExec();
}
std::string Request::getFileName(void) const
{
    return this->_parser.getFileName();
}

void Request::setFileExec(std::string fileExec)
{
    this->_parser.setFileExec(fileExec);
}

void Request::setBody(std::string newBody)
{
    this->_parser.setBody(newBody);
}

void Request::setPath(std::string newPath)
{
    this->_parser.setPath(newPath);
}

void Request::buildCGI(void)
{
    setPath("/assets/cgi_temp.html");
}
