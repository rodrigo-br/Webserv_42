#include "tests.hpp"

TEST_CASE("hasMethodInInput retorna true para GET com valores 1, 3 e 5 e 7")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(1, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(3, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(5, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(7, HttpMethodEnum::GET));

    REQUIRE(hasGet == true);
}

TEST_CASE("hasMethodInInput retorna false para GET com valores 2, 4, 6, 8 e diferentes")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(2, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(4, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(6, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(8, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(0, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(9, HttpMethodEnum::GET),
                            Utils::hasMethodInInput(10, HttpMethodEnum::GET));

    REQUIRE(hasGet == false);
}

TEST_CASE("hasMethodInInput retorna true para POST com valores 2, 3 e 6 e 7")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(2, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(3, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(6, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(7, HttpMethodEnum::POST));

    REQUIRE(hasGet == true);
}

TEST_CASE("hasMethodInInput retorna false para POST com valores 1, 4, 5, 8 e diferentes")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(1, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(4, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(5, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(8, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(0, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(9, HttpMethodEnum::POST),
                            Utils::hasMethodInInput(10, HttpMethodEnum::POST));

    REQUIRE(hasGet == false);
}

TEST_CASE("hasMethodInInput retorna true para POST com valores 4, 5 e 6 e 7")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(4, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(5, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(6, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(7, HttpMethodEnum::DELETE));

    REQUIRE(hasGet == true);
}

TEST_CASE("hasMethodInInput retorna false para DELETE com valores 1, 2, 3, 8 e diferentes")
{
    bool hasGet = GENERATE(Utils::hasMethodInInput(1, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(2, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(3, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(8, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(0, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(9, HttpMethodEnum::DELETE),
                            Utils::hasMethodInInput(10, HttpMethodEnum::DELETE));

    REQUIRE(hasGet == false);
}
