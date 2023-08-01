#include "tests.hpp"

char request_image[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Windows\"\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\nSec-Purpose: prefetch;prerender\r\nPurpose: prefetch\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\nCookie: wp-settings-time-1=16874782750;";

char request_curl[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*";


TEST_CASE("Testando se o parser request acha o header user-agent num request")
{
    RequestParser requestParser;
    requestParser.parser_http_request(request_curl);

    std::string user_agent = requestParser.get_user_agent();
    std::string expectd = "curl/7.81.0";

    REQUIRE(user_agent == expectd);
}

TEST_CASE("Testando se o parser request acha o header user-agent de uma imagem num request")
{
    RequestParser requestParser;
    requestParser.parser_http_request(request_image);

    std::string user_agent = requestParser.get_user_agent();
    std::string expectd = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36";

    REQUIRE(user_agent == expectd);
}

TEST_CASE("Testando se o parser request acha o header host de uma imagem num request")
{
    RequestParser requestParser;
    requestParser.parser_http_request(request_image);

    std::string user_agent = requestParser.get_host();
    std::string expectd = "localhost:8000";

    REQUIRE(user_agent == expectd);
}


TEST_CASE("Testando se o parser request acha o header host num request")
{
    RequestParser requestParser;
    requestParser.parser_http_request(request_curl);

    std::string user_agent = requestParser.get_host();
    std::string expectd = "localhost:8000";

    REQUIRE(user_agent == expectd);
}
