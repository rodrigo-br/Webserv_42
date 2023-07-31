#include "tests.hpp"

TEST_CASE ("OK GET request method Header")
{
    Response response;

    std::string response_header = response.get_response();

    REQUIRE(response_header.compare("HTTP/1.1 200 OK\r\nContent-Type: image/png\r\n\n") == 0);
}

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
