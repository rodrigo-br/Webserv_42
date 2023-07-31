#include "tests.hpp"

TEST_CASE ("Listen do conf retorna porta correta do arquivo")
{
    // Criar e usar arquivos de configuração
    Conf conf;

    int port = conf.get_listen();

    REQUIRE(port == 8000);
}

TEST_CASE ("Root do conf retorna root correto do arquivo")
{
    // Criar e usar arquivos de configuração
    Conf conf;

    std::string root = conf.get_root();

    REQUIRE(root == "/");
}

TEST_CASE ("Listen do conf retorna listens corretos do arquivo")
{
    // Criar e usar arquivos de configuração
    Conf conf;

    std::map<std::string, std::string> locations = conf.get_locations();

    REQUIRE(locations["/"] == "index.html");
}
