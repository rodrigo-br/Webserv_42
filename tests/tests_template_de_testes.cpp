/*
    Este arquivo é apenas uma demonstração.
    Deletar-me antes da entrega do projeto!
*/

// Inclua o header de tests.hpp, se todas as classes estiverem incluídas
// no arquivo webserv.hpp, não será necessário fazer mais nenhuma inclusão
#include "tests.hpp"

// Um teste simples precisa apenas desse formato TEST_CASE("Título") {AAA}
// AAA = Arrange, Act, Assert. Google it.
TEST_CASE ("String cavalinho vira só cavalinho")
{
    // Arrange
    std::string cavalinho("cavalinho na chuva ao vento");

    // Act
    cavalinho = cavalinho.substr(0, 9);

    // Assert
    REQUIRE(cavalinho == "cavalinho");
}

// Read the doc to more cases : https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md