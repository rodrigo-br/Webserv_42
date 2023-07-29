#include "tests.hpp"

TEST_CASE ("Resposta possui header válido")
{

}


TEST_CASE ("Resposta 200 para OK")
{
    ResponseBuilder responseBuilder;

    std::string status_code = responseBuilder.get_status_code();
    std::string status_message = responseBuilder.get_status_msg();

    REQUIRE(status_code.compare("200 ") == 0);
    REQUIRE(status_message.compare("OK") == 0);
}

TEST_CASE ("Resposta 400 para request inválido")
{

}


TEST_CASE ("Resposta 404 para conteúdo não encontrado")
{

}

TEST_CASE ("Resposta 500 para erro interno no servidor")
{

}
