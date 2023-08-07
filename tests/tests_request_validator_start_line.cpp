#include "tests.hpp"

TEST_CASE("Testando se o request validator acha o método GET num GET request")
{
    char requestMensage[] = "GET / HTTP/1.1\n";
    Conf conf;
    Request request;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    HttpMethodEnum::httpMethod method = request_validator.get_method();

    REQUIRE(method == HttpMethodEnum::GET);
}
TEST_CASE("Testando se o request validator acha o método POST num POST request")
{
    char requestMensage[] = "POST / HTTP/1.1\n";
    Conf conf;
    Request request;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    HttpMethodEnum::httpMethod method = request_validator.get_method();

    REQUIRE(method == HttpMethodEnum::POST);
}

TEST_CASE("Testando se o request validator acha o método DELETE num DELETE request")
{
    char requestMensage[] = "DELETE / HTTP/1.1\n";
    Conf conf;
    Request request;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    HttpMethodEnum::httpMethod method = request_validator.get_method();

    REQUIRE(method == HttpMethodEnum::DELETE);
}

TEST_CASE("Testando se o request validator acha o método desconehcido num request")
{
    char requestMensage[] = "UNKNOWN / HTTP/1.1\n";
    Request request;
    request._parser.parser_http_request(requestMensage);
    Conf conf;
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    HttpMethodEnum::httpMethod method = request_validator.get_method();

    REQUIRE(method == HttpMethodEnum::UNKNOWN);
}

TEST_CASE("Testando se o request validator acha o PATH / num request")
{
    char requestMensage[] = "GET / HTTP/1.1\n";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = true;
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request validator acha o PATH /index.html num request")
{
    char requestMensage[] = "GET /index.html HTTP/1.1\n";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = true;
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request validator da false se achar o Referer do PATH /assets/Dogs.png num request")
{
    char requestMensage[] = "GET /assets/Dogs.png HTTP/1.1\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nReferer: http://localhost:8000/assets/Dogs.png\r\nContent-Length: 42\r\n ";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = true;
    REQUIRE(path == expectd);
}


TEST_CASE("Testando se o request validator acha o PATH /cavalinho.html  num request")
{
    char requestMensage[] = "GET /cavalinho.html HTTP/1.1\n";
      Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = false;
    REQUIRE(path == expectd);
}

TEST_CASE("Testando se o request validator acha o http request é HTTP/1.1 num request")
{
    char requestMensage[] = "GET /cavalinho.html HTTP/1.1\n";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool http_version = request_validator.get_http_version();
    bool expectd = true;
    REQUIRE(http_version == expectd);
}

TEST_CASE("Testando se o request validator acha o http request é HTTP/1.2 num request e da erro")
{
    char requestMensage[] = "GET /cavalinho.html HTTP/1.2\n";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool http_version = request_validator.get_http_version();
    bool expectd = false;
    REQUIRE(http_version == expectd);
}

TEST_CASE( "Testando se tudo dá true")
{
    std::string requestMensage = GENERATE("GET /api/api.html HTTP/1.1\n", 
                                       "GET /api/upload/upload.html HTTP/1.1\n",
                                        "GET /images/images.html HTTP/1.1\n",
                                         "GET /images/random/index.html HTTP/1.1\n" );

    Request request;
    Conf conf;
    request._parser.parser_http_request(const_cast<char*>(requestMensage.c_str()));
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = true;
    REQUIRE(path == expectd);
               
}


TEST_CASE("Testando se o request validator da false se nao achar o Referer do PATH /assets/Dogs.png num request")
{
    char requestMensage[] = "GET /assets/Dogs.png HTTP/1.1\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 42\r\n ";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = false;
    REQUIRE(path == expectd);
}
TEST_CASE("Testando se o request validator da false se nao achar o Referer do PATH cavalinhp/assets/Dogs.png num request")
{
    char requestMensage[] = "GET cavalinhp/assets/Dogs.png HTTP/1.1\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 42\r\n ";
    Request request;
    Conf conf;
    request._parser.parser_http_request(requestMensage);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool path = request_validator.get_path();
    bool expectd = false;
    REQUIRE(path == expectd);
}