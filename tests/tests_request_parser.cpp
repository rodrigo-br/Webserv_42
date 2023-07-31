#include "tests.hpp"

TEST_CASE("Testando se o parser request acha o método get num get request")
{
    RequestParser requestParser = RequestParser("GET / HTTP/1.1\n");

    HttpMethodEnum::httpMethod method = requestParser.get_method();

    REQUIRE(method == HttpMethodEnum::GET);
    REQUIRE(requestParser._line == "/ HTTP/1.1\n");
}