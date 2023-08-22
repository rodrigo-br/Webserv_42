#include "tests.hpp"

char request_query[] = "GET /? HTTP/1.1\r\nHost: localhost:8000\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Windows\"\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\nSec-Purpose: prefetch;prerender\r\nPurpose: prefetch\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\nCookie: wp-settings-time-1=16874782750;";

char request_query2[] = "GET /path?query_strin HTTP/1.1\r\nHost: localhost:1024 \r\nUser-Agent: curl/7.81.0\r\nAccept: */*";

char request_query3[] = "GET /index.html/?NAME=lari HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.81.0\r\nAccept: */*";
char request_query4[] = "GET /page?param1=value1&param2=value2 HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.81.0\r\nAccept: */*";


TEST_CASE("Request query ?")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_query);
    
        std::string port  = requestParser.getQuery();
        std::string expected = "";

        REQUIRE(port == expected);
}

TEST_CASE("Request query query_strin")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_query2);
    
        std::string port  = requestParser.getQuery();
        std::string expected = "query_strin";

        REQUIRE(port == expected);
}

TEST_CASE("Request query NAME=lari")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_query3);
    
        std::string port  = requestParser.getQuery();
        std::string expected = "NAME=lari";

        REQUIRE(port == expected);
}

TEST_CASE("Request query param1=value1&param2=value2")
{
    RequestParser requestParser;
    requestParser.parserHttpRequest(request_query4);
    
        std::string port  = requestParser.getQuery();
        std::string expected = "param1=value1&param2=value2";

        REQUIRE(port == expected);
}