#include "classes/Request.hpp"

Request::Request( int fd_connection ) : _request()
{
    if (Utils::check(read(fd_connection, _request, BUFFER_SIZE), 0))
	{
		exit(EXIT_FAILURE);
	}
}

Request::~Request( void ) { }

const char*    Request::get_request( void ) const
{
    return (this->_request);
}
