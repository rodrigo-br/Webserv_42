#include "classes/Request.hpp"

Request::Request( int fd_connection ) : _request()
{
    if (check(read(fd_connection, _request, BUFFER_SIZE), 0))
	{
		exit(EXIT_FAILURE);
	}

}

Request::~Request( void ) { }

bool Request::check(ssize_t result, int erro)
{
	if (result <= erro)
	{
		std::cout << std::strerror(errno) << std::endl;
	}
	return (result <= erro);
}


const char*    Request::get_request( void ) const
{
    return (this->_request);
}
