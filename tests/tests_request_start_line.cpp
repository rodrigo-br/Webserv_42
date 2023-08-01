#include "tests.hpp"

TEST_CASE("Testando se o request acha o método GET num GET request")
{
    char requestMensage[] = "GET / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    HttpMethodEnum::httpMethod method = request.get_method();

    REQUIRE(method == HttpMethodEnum::GET);
}

TEST_CASE("Testando se o request acha o método POST num POST request")
{
    char requestMensage[] = "POST / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    HttpMethodEnum::httpMethod method = request.get_method();

    REQUIRE(method == HttpMethodEnum::POST);
}

TEST_CASE("Testando se o request acha o método DELETE num DELETE request")
{
    char requestMensage[] = "DELETE / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    HttpMethodEnum::httpMethod method = request.get_method();

    REQUIRE(method == HttpMethodEnum::DELETE);
}

TEST_CASE("Testando se o request acha o método desconehcido num request")
{
    char requestMensage[] = "UNKNOWN / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    HttpMethodEnum::httpMethod method = request.get_method();

    REQUIRE(method == HttpMethodEnum::UNKNOWN);
}

TEST_CASE("Testando se o request acha o PATH / num request")
{
    char requestMensage[] = "GET / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    std::string path = request.get_path();
    std::string expectd = "/";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request acha o PATH /index.html num request")
{
    char requestMensage[] = "GET /index.html HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    std::string path = request.get_path();
    std::string expectd = "/index.html";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request acha o PATH /files/cavalinho.html  num request")
{
    char requestMensage[] = "GET /files/cavalinho.html HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    std::string path = request.get_path();
    std::string expectd = "/files/cavalinho.html";
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request acha o http request é HTTP/1.1 num request")
{
    char requestMensage[] = "GET /files/cavalinho.html HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    std::string http_version = request.get_http_version();
    std::string expectd = "HTTP/1.1";
    REQUIRE(http_version == expectd);
}


TEST_CASE("Testando se o request acha o http request é HTTP/1.2 num request e da erro")
{
    char requestMensage[] = "GET /files/cavalinho.html HTTP/1.2\n";
    Request request;
    request._parser.parser_http_request(requestMensage);

    std::string http_version = request.get_http_version();
    std::string expectd = "HTTP/1.1";
    REQUIRE(http_version != expectd);
}
