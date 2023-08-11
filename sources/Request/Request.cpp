#include "classes/Request.hpp"

Request::Request( ) : _request() {	}

Request::~Request( void ) { }

const char*    Request::getMensageRequest( void ) const
{
    return (this->_request);
}

Request			&Request::createParsedMessage(int fdConnection)
{
	if (Utils::check(read(fdConnection,this->_request, BUFFER_SIZE), 0))
	{
		exit(EXIT_FAILURE);
	}
	this->_parser.parserHttpRequest(this->_request);
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

std::string Request::getHttpVersion(void) const
{
    return this->_parser.getHttpVersion();
}

std::string Request::getBody(void) const
{
    return this->_parser.getBody();
}

std::string Request::getHeader(std::string headerName ) const
{
    return this->_parser.getHeader(headerName);
}

void Request::setPath(std::string newPath)
{
    this->_parser.setPath(newPath);
}
