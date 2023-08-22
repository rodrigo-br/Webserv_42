#include "tests.hpp"

char request_cgi[] = "GET /cgi-bin/index.py HTTP/1.1\r\nHost: localhost:8000\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nReferer: http://localhost:8000/cgi-bin\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: pt,pt-BR;q=0.9,en-US;q=0.8,en;q=0.7\r\nCookie: _ga=GA1.1.2145259009.1689619969; _ga_G2JSW5YPMJ=GS1.1.1692701198.76.1.1692704093.0.0.0; _ga_H6LPQNDD8W=GS1.1.1692701198.75.1.1692704093.60.0.0\r\n";

TEST_CASE("Cgi::createEnvironmentArray()")
{   
	Request request;
	ServerData serverData;
	Cgi cgi(request, serverData.getPort());
	cgi.createEnvironmentArray();

	REQUIRE(cgi._envp != nullptr);
	std::map<std::string, std::string>::const_iterator it;
	int i = 0;
	for (it = cgi._env.begin(); it != cgi._env.end(); ++it, ++i) 
	{
		std::string expected = it->first + "=" + it->second;
		REQUIRE(std::string(cgi._envp [i]) == expected);
	}
	REQUIRE(cgi._envp [i] == nullptr); 
	cgi.freeArrayOfStrings(cgi._envp );
}

TEST_CASE("Cgi::createArrayOfStrings()")
{   
	Request request;
	request._parser.parserHttpRequest(request_cgi);
	Cgi cgi(request);
	cgi.initScriptArguments(request);

	REQUIRE(std::string(cgi._args[0]) == "python3");
	REQUIRE(std::string(cgi._args[1]) == cgi._fileScript);
	REQUIRE(std::string(cgi._args[2]) == request.getBody());
	REQUIRE(cgi._args[3] == NULL);
	cgi.freeArrayOfStrings(cgi._args);
}