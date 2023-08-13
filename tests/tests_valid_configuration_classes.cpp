#include "tests.hpp"

TEST_CASE("Testa se portas válidas dão true na configuração de server")
{
    ValidConfigurations validConfigurations;
    std::string key = "listen";
    std::string value = GENERATE("8000", "1025", "49150", "1718", "1725", "8080");

    bool isValidConfiguration = validConfigurations.ValidateAServerConfiguration(key, value);

    REQUIRE(isValidConfiguration == true);
}

TEST_CASE("Testa se portas inválidas dão false na configuração de server")
{
    ValidConfigurations validConfigurations;
    std::string key = "listen";
    std::string value = GENERATE("0","1024","1719","1723","2049","3659","4045","5060","5061","6000"
        ,"6566","6665","6666","6667","6668","6669","6697","10080","1023","49151","49152","-1", "cavalinho");

    bool isValidConfiguration = validConfigurations.ValidateAServerConfiguration(key, value);

    REQUIRE(isValidConfiguration == false);
}

TEST_CASE("Testa keys inválidas dão false na configuração de server no geral")
{
    ValidConfigurations validConfigurations;
    std::string key = GENERATE("0","8000","-1","cavalinho","serv","camilla","lucas","do","mal","listenm");
    std::string value = "8000";

    bool isValidConfiguration = validConfigurations.ValidateAServerConfiguration(key, value);

    REQUIRE(isValidConfiguration == false);
}

TEST_CASE("Testa roots válidos dão true na configuração de server")
{
    ValidConfigurations validConfigurations;
    std::string key = "root";
    std::string value = GENERATE("wwwroot","wwwroot/api","wwwroot/assets","wwwroot/images","conf","sources");

    bool isValidConfiguration = validConfigurations.ValidateAServerConfiguration(key, value);

    REQUIRE(isValidConfiguration == true);
}

TEST_CASE("Testa roots inválidos dão false na configuração de server")
{
    ValidConfigurations validConfigurations;
    std::string key = "root";
    std::string value = GENERATE("wwwroot1","wwwroot//api","/wwwroot/assets",".wwwroot/images/images.html","confi"
                                ,"sourrces", "..", "../", "../Webserv_42/wwwroot", "wwwroot/index.html");

    bool isValidConfiguration = validConfigurations.ValidateAServerConfiguration(key, value);

    REQUIRE(isValidConfiguration == false);
}

TEST_CASE("Testa http_methods válidos dão true na configuração de location")
{
    ValidConfigurations validConfigurations;
    std::string key = "http_methods";
    std::string value = GENERATE("1","2","3","4","5","6","7");

    bool isValidConfiguration = validConfigurations.ValidateALocationConfiguration(key, value);

    REQUIRE(isValidConfiguration == true);
}

TEST_CASE("Testa http_methods inválidos dão false na configuração de location")
{
    ValidConfigurations validConfigurations;
    std::string key = "http_methods";
    std::string value = GENERATE("wwwroot1","0","-1","8","8000"
                                ,"..","../","cavalinho");

    bool isValidConfiguration = validConfigurations.ValidateALocationConfiguration(key, value);

    REQUIRE(isValidConfiguration == false);
}

TEST_CASE("Testa index válidos dão true na configuração de location")
{
    ValidConfigurations validConfigurations;
    std::string key = "index";
    std::string value = GENERATE("wwwroot/index.html","wwwroot/404.html","Makefile","README.md");

    bool isValidConfiguration = validConfigurations.ValidateALocationConfiguration(key, value);

    REQUIRE(isValidConfiguration == true);
}

TEST_CASE("Testa index inválidos dão false na configuração de location")
{
    ValidConfigurations validConfigurations;
    std::string key = "index";
    std::string value = GENERATE("wwwroot1","0","-1","8","8000"
                                ,"..","../","cavalinho");

    bool isValidConfiguration = validConfigurations.ValidateALocationConfiguration(key, value);

    REQUIRE(isValidConfiguration == false);
}
