#include "tests.hpp"

char request_curl_body[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 42\r\n\r\n{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
char request_curl_body2[] = "POST /api/endpoint HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 33\r\n\r\npart1=Hello&part2=World&part3=123";

char request_curl1[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 42\r\n";
char request_curl2[] = "POST /api/endpoint HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 33\r\n";

TEST_CASE("Testando se o request validator retorna true no body num request")
{
    Request request;
    Conf conf(new ConfParser("./conf/default.conf"));
    request._parser.parser_http_request(request_curl_body);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool body = request_validator.get_body();
    bool expectd = true;

    REQUIRE(body == expectd);
    conf.deleteConfParser();
}

TEST_CASE("Testando se o parser validator retorna true no body2 num request")
{
    Request request;
    Conf conf(new ConfParser("./conf/default.conf"));
    request._parser.parser_http_request(request_curl_body2);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool body = request_validator.get_body();
    bool expectd = true;

    REQUIRE(body == expectd);
    conf.deleteConfParser();
}

TEST_CASE("Testando se o parser validator retorna false no o curl num request")
{
    Request request;
    Conf conf(new ConfParser("./conf/default.conf"));
    request._parser.parser_http_request(request_curl1);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool body = request_validator.get_body();
    bool expectd = false;

    REQUIRE(body == expectd);
    conf.deleteConfParser();
}

TEST_CASE("Testando se o parser validator retorna false no o curl2 num request")
{
    Request request;
    Conf conf(new ConfParser("./conf/default.conf"));
    request._parser.parser_http_request(request_curl2);
    RequestValidator request_validator = RequestValidator().request_validator(conf, request);

    bool body = request_validator.get_body();
    bool expectd = false;

    REQUIRE(body == expectd);
    conf.deleteConfParser();
}
