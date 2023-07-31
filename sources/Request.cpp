#include "classes/Request.hpp"

Request::Request( int fd_connection ) : _request()
{
    if (Utils::check(read(fd_connection,this-> _request, BUFFER_SIZE), 0))
	{
		exit(EXIT_FAILURE);
	}
	this->_parser.parser_http_request(this->_request);
	// Request::_method = requestParser.set_method();

}

Request::~Request( void ) { }

const char*    Request::get_request( void ) const
{
    return (this->_request);
}

// HttpMethodEnum::httpMethod	Request::get_method( void )
// {
// 	return()
// }