#include "tests.hpp"

TEST_CASE("Deve retornar extensão .html para todos os generators")
{
    MethodsUtils methosdUtils;
    std::string mock_paths = GENERATE("index.html", "cavalinho.html", ".html", "html.html", "index.cs.html", "index.cs.index.html");

    std::string extension = methosdUtils.get_extension(mock_paths);

    REQUIRE(extension == ".html");
}

TEST_CASE("Deve retornar extensão .bin para todos os generators")
{
    MethodsUtils methosdUtils;
    std::string mock_paths = GENERATE("", "cavalinho", "cavalinho.bin", "html.html.bin", "index.cs.html.bin");

    std::string extension = methosdUtils.get_extension(mock_paths);

    REQUIRE(extension == ".bin");
}
