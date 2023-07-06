#include "tests.hpp"

TEST_CASE ("Testando se a porta é igual a 8000")
{
    Server server;
    REQUIRE(server.getPort() == 8000);
}
