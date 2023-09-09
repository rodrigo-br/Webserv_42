// #include "tests.hpp"

// TEST_CASE("Testando se o parser request acha o método GET num GET request")
// {
//     char request[] = "GET / HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string method = requestParser.getMethod();

//     REQUIRE(method == "GET");
// }

// TEST_CASE("Testando se o parser request acha o método POST num POST request")
// {
//     char request[] = "POST / HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string method = requestParser.getMethod();

//     REQUIRE(method ==  "POST");
// }

// TEST_CASE("Testando se o parser request acha o método DELETE num DELETE request")
// {
//     char request[] = "DELETE / HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string method = requestParser.getMethod();

//     REQUIRE(method ==  "DELETE");
// }

// TEST_CASE("Testando se o parser request acha o método desconehcido num request")
// {
//     char request[] = "UNKNOWN / HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string method = requestParser.getMethod();

//     REQUIRE(method == "UNKNOWN");
// }

// TEST_CASE("Testando se o parser request acha o PATH / num request")
// {
//     char request[] = "GET / HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string path = requestParser.getPath();
//     std::string expectd = "/";
//     REQUIRE(path == expectd);
// }

// TEST_CASE("Testando se o parser request acha o PATH /index.html num request")
// {
//     char request[] = "GET /index.html HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string path = requestParser.getPath();
//     std::string expectd = "/index.html";
//     REQUIRE(path == expectd);
// }

// TEST_CASE("Testando se o parser request acha o PATH /wwwroot/cavalinho.html  num request")
// {
//     char request[] = "GET /wwwroot/cavalinho.html HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string path = requestParser.getPath();
//     std::string expectd = "/wwwroot/cavalinho.html";
//     REQUIRE(path == expectd);
// }

// TEST_CASE("Testando se o parser request acha o http request é HTTP/1.1 num request")
// {
//     char request[] = "GET /wwwroot/cavalinho.html HTTP/1.1\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string http_version = requestParser.getHttpVersion();
//     std::string expectd = "HTTP/1.1";
//     REQUIRE(http_version == expectd);
// }


// TEST_CASE("Testando se o parser request acha o http request é HTTP/1.2 num request e da erro")
// {
//     char request[] = "GET /wwwroot/cavalinho.html HTTP/1.2\n";
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(request);

//     std::string http_version = requestParser.getHttpVersion();
//     std::string expectd = "HTTP/1.1";
//     REQUIRE(http_version != expectd);
// }
