#include "classes/Request.hpp"

Request::Request( ) : _request() {	}

Request::~Request( void ) { }

const char*    Request::get_mensage_request( void ) const
{
    return (this->_request);
}

Request			&Request::create_parsed_message(int fd_connection)
{
	if (Utils::check(read(fd_connection,this->_request, BUFFER_SIZE), 0))
	{
		exit(EXIT_FAILURE);
	}
	this->_parser.parser_http_request(this->_request);
	return *this;
}

std::string Request::get_method() const
{
    return this->_parser.get_method();
}

std::string Request::get_path(void) const
{
    return this->_parser.get_path();
}

std::string Request::get_http_version(void) const
{
    return this->_parser.get_http_version();
}

std::string Request::get_body(void) const
{
    return this->_parser.get_body();
}

std::string Request::get_header(std::string header_name ) const
{
    return this->_parser.get_header(header_name);
}

void Request::set_path(std::string new_path)
{
    this->_parser.set_path(new_path);
}
