#include "classes/Request.hpp"

Request::Request( ) : _request()
{
	
}

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

HttpMethodEnum::httpMethod Request::get_method()
{
    return _parser.get_method();
}

std::string Request::get_path(void)
{
    return _parser.get_path();
}

std::string Request::get_http_version(void)
{
    return _parser.get_http_version();
}

std::string Request::get_user_agent(void)
{
    return _parser.get_user_agent();
}

std::string Request::get_host(void)
{
    return _parser.get_host();
}
