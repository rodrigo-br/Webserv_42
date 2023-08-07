#include "tests.hpp"

// TEST_CASE ("OK GET request method Header")
// {
//     Conf conf;
//     int fd_connection = fileno(tmpfile());
//     Request request = Request().create_parsed_message(fd_connection);
//     RequestValidator request_validator = RequestValidator().request_validator(conf, request);
// 	Response response(new ResponseBuilder(request, request_validator));

//     std::string response_header = response.get_response();

//     REQUIRE(response_header.compare("HTTP/1.1 200 OK\r\nContent-Type: image/png\r\n\n") == 0);
// }

TEST_CASE ("OK POST request method Header")
{

}

TEST_CASE ("OK PUT request method Header")
{

}

TEST_CASE  ("OK DELETE request method Header")
{

}

TEST_CASE ("OK OPTIONS request method Header")
{

}
