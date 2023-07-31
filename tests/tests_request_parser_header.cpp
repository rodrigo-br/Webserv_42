#include "tests.hpp"

// char request[] = "GET / HTTP/1.1\r\n"
//     "Host: localhost:8000\r\n"
//     "Connection: keep-alive\r\n"
//     "sec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\n"
//     "sec-ch-ua-mobile: ?0\r\n"
//     "sec-ch-ua-platform: \"Windows\"\r\n"
//     "Upgrade-Insecure-Requests: 1\r\n"
//     "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\n"
//     "Sec-Purpose: prefetch;prerender\r\n"
//     "Purpose: prefetch\r\n"
//     "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\n"
//     "Sec-Fetch-Site: none\r\n"
//     "Sec-Fetch-Mode: navigate\r\n"
//     "Sec-Fetch-User: ?1\r\n"
//     "Sec-Fetch-Dest: document\r\n"
//     "Accept-Encoding: gzip, deflate, br\r\n"
//     "Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
//     "Cookie: wp-settings-time-1=16874782750;";

// TEST_CASE("Testando se o parser request acha o header user-agent num request")
// {
//     RequestParser requestParser;
//     requestParser.parser_http_request(request);

//     std::string user_agent = requestParser._user_agent;
//     std::string expectd = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\n";

//     REQUIRE(user_agent == expectd);
// }