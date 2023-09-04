// #include "tests.hpp"

// char request_curl_bory[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 42\r\n\r\n{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";

// char request_curl_bory2[] = "POST /api/endpoint HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 33\r\n\r\npart1=Hello&part2=World&part3=123";

// TEST_CASE("Testando se o parser request acha o bory num request")
// {
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request_curl_bory);

//     std::string body = requestParser.getBody();
//     std::string expectd = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";

//     REQUIRE(body == expectd);
// }

// TEST_CASE("Testando se o parser request acha o bory2 num request")
// {
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request_curl_bory2);

//     std::string body = requestParser.getBody();
//     std::string expectd = "part1=Hello&part2=World&part3=123";

//     REQUIRE(body == expectd);
// }
