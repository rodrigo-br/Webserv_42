#include "tests.hpp"

TEST_CASE("Testando se o parser request acha o método GET num GET request")
{
    char request[] = "GET / HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    HttpMethodEnum::httpMethod method = requestParser.get_method();

    REQUIRE(method == HttpMethodEnum::GET);
}

TEST_CASE("Testando se o parser request acha o método POST num POST request")
{
    char request[] = "POST / HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    HttpMethodEnum::httpMethod method = requestParser.get_method();

    REQUIRE(method == HttpMethodEnum::POST);
}

TEST_CASE("Testando se o parser request acha o método DELETE num DELETE request")
{
    char request[] = "DELETE / HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    HttpMethodEnum::httpMethod method = requestParser.get_method();

    REQUIRE(method == HttpMethodEnum::DELETE);
}

TEST_CASE("Testando se o parser request acha o método desconehcido num request")
{
    char request[] = "UNKNOWN / HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    HttpMethodEnum::httpMethod method = requestParser.get_method();

    REQUIRE(method == HttpMethodEnum::UNKNOWN);
}

TEST_CASE("Testando se o parser request acha o PATH / num request")
{
    char request[] = "GET / HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    std::string path = requestParser.get_path();
    std::string expectd = "/";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o parser request acha o PATH /index.html num request")
{
    char request[] = "GET /index.html HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    std::string path = requestParser.get_path();
    std::string expectd = "/index.html";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o parser request acha o PATH /files/cavalinho.html  num request")
{
    char request[] = "GET /files/cavalinho.html HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    std::string path = requestParser.get_path();
    std::string expectd = "/files/cavalinho.html";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o parser request acha o http request é HTTP/1.1 num request")
{
    char request[] = "GET /files/cavalinho.html HTTP/1.1\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    std::string http_version = requestParser.get_http_version();
    std::string expectd = "HTTP/1.1";
    REQUIRE(http_version == expectd);
}


TEST_CASE("Testando se o parser request acha o http request é HTTP/1.2 num request e da erro")
{
    char request[] = "GET /files/cavalinho.html HTTP/1.2\n";
    RequestParser requestParser;
    requestParser.parser_http_request(request);

    std::string http_version = requestParser.get_http_version();
    std::string expectd = "HTTP/1.1";
    REQUIRE(http_version != expectd);
}
