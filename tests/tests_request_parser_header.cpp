#include "tests.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <sys/un.h>
// char request_image[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not/A)Brand\";v=\"99\", \"Google Chrome\";v=\"115\", \"Chromium\";v=\"115\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Windows\"\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36\r\nSec-Purpose: prefetch;prerender\r\nPurpose: prefetch\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: ?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\nCookie: wp-settings-time-1=16874782750;";

// char request_curl[] = "GET / HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.81.0\r\nAccept: */*";


TEST_CASE("Request curl")
{
    RequestParser requestParser;
    const char* socket_path = "/tmp/test_sock";
    // Criar um soquete de domínio Unix (local) simulado
    int test_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (test_socket == -1) {
        perror("Erro ao criar o soquete de teste");
        return;
    }

    int reuse = 1;
    if (setsockopt(test_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("Erro ao definir a opção SO_REUSEADDR");
        close(test_socket);
        return;
    }
    struct sockaddr_un socket_address;
    socket_address.sun_family = AF_UNIX;
    strncpy(socket_address.sun_path, socket_path, sizeof(socket_address.sun_path));
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    // Simular a aceitação de uma conexão no soquete simulado
    if (bind(test_socket, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1) {
        perror("Erro ao vincular o soquete simulado");
        close(test_socket);
        return;
    }

    // Aguardar uma conexão simulada (como se fosse o servidor)
    if (listen(test_socket, 5) == -1) {
        perror("Erro ao ouvir no soquete simulado");
        close(test_socket);
        return;
    }

    // Aceitar a conexão simulada
    int client_socket = accept(test_socket, nullptr, nullptr);
    if (client_socket == -1) {
        perror("Erro ao aceitar a conexão simulada");
        close(test_socket);
        return;
    }

    // Simular uma solicitação HTTP como uma string
    std::string http_request = "GET /my_custom_path HTTP/1.1\r\n";
    http_request += "Host: localhost:8000\r\n";
    http_request += "User-Agent: curl/7.81.0\r\n";
    http_request += "Accept: */*\r\n\r\n";

    // Enviar a solicitação simulada para o cliente simulado (como se fosse o servidor)
    ssize_t bytes_written = write(client_socket, http_request.c_str(), http_request.size());
    if (bytes_written == -1) {
        perror("Erro ao escrever a solicitação HTTP no cliente simulado");
        close(client_socket);
        close(test_socket);
        return;
    }

    requestParser.parserHttpRequest(test_socket);

    SECTION("Testando se o parser request acha o header user-agent num request")
    {
        std::string header = requestParser.getHeader("User-Agent");
        std::string expected = "curl/7.81.0";
        REQUIRE(header == expected);
    }

    SECTION("Testando se o parser request acha o header host num request")
    {
        std::string header = requestParser.getHeader("Host");
        std::string expected = "localhost:8000";
        REQUIRE(header == expected);
    }

    SECTION("Testando se o parser request acha o header Accept num request")
    {
        std::string header = requestParser.getHeader("Accept");
        std::string expected = "*/*"; // Corrigido aqui
        REQUIRE(header == expected);
    }

    // Fechar os soquetes após todos os testes
    close(client_socket);
    close(test_socket);
    rmdir(socket_path);
}


// TEST_CASE("Request curl image")
// {
//     RequestParser requestParser;
//     requestParser.parserHttpRequest(http_request);

//     SECTION("Testando se o parser request acha o header host num request")
//     {
//         std::string header  = requestParser.getHeader("Host");
//         std::string expectd = "localhost:8000";

//         REQUIRE(header == expectd);
//     }

//     SECTION("Testando se o parser request acha o header Accept num request")
//     {
//         std::string header  = requestParser.getHeader("Accept");
//         std::string expectd = "*/*";

//         REQUIRE(header == expectd);
//     }

//     SECTION("Testando se o parser request acha o header user-agent num request")
//     {
//         std::string header  = requestParser.getHeader("User-Agent");
//         std::string expected = "curl/7.81.0";

//         REQUIRE(header == expected);
//     }
// }
