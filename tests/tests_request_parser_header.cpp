#include "tests.hpp"

char request_image[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Windows\"\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\nSec-Purpose: prefetch;prerender\r\nPurpose: prefetch\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\nCookie: wp-settings-time-1=16874782750;";

char request_curl[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*";

TEST_CASE("Request curl")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_curl);

    SECTION("Testando se o parser request acha o header user-agent num request")
    {
        std::string header  = requestParser.getHeader("User-Agent");
        std::string expected = "curl/7.81.0";

        REQUIRE(header == expected);
    }

    SECTION("Testando se o parser request acha o header host num request")
    {
        std::string header  = requestParser.getHeader("Host");
        std::string expectd = "localhost:8000";

        REQUIRE(header == expectd);
    }

    SECTION("Testando se o parser request acha o header Accept num request")
    {
        std::string header  = requestParser.getHeader("Accept");
        std::string expectd = "*/*";

        REQUIRE(header == expectd);
    }
}


TEST_CASE("Request curl image")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_curl);

    SECTION("Testando se o parser request acha o header host num request")
    {
        std::string header  = requestParser.getHeader("Host");
        std::string expectd = "localhost:8000";

        REQUIRE(header == expectd);
    }

    SECTION("Testando se o parser request acha o header Accept num request")
    {
        std::string header  = requestParser.getHeader("Accept");
        std::string expectd = "*/*";

        REQUIRE(header == expectd);
    }

    SECTION("Testando se o parser request acha o header user-agent num request")
    {
        std::string header  = requestParser.getHeader("User-Agent");
        std::string expected = "curl/7.81.0";

        REQUIRE(header == expected);
    }
}
