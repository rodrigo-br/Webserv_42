#include "tests.hpp"

TEST_CASE("Config parser succeed retorna TRUE para arquivos VÁLIDOS")
{
    std::string confPath = GENERATE("tests/confs/validos/valid_01.conf",
                                    "tests/confs/validos/valid_02.conf",
                                    "tests/confs/validos/valid_03.conf",
                                    "tests/confs/validos/valid_04.conf");

    ConfParser confParser(confPath);

    REQUIRE(confParser.succeed() == true);
}

TEST_CASE("Config parser succeed retorna FALSE para arquivos INVÁLIDOS")
{
    std::string confPath = GENERATE("tests/confs/invalidos/invalid_01.conf",
                                    "tests/confs/invalidos/invalid_02.conf",
                                    "tests/confs/invalidos/invalid_03.conf",
                                    "tests/confs/invalidos/invalid_04.conf",
                                    "tests/confs/invalidos/invalid_05.conf",
                                    "tests/confs/invalidos/invalid_06.conf",
                                    "tests/confs/invalidos/invalid_07.conf");

    ConfParser confParser(confPath);

    REQUIRE(confParser.succeed() == false);
}
