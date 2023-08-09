#include "classes/ConfParser.hpp"

ConfParser::ConfParser(std::string file)
{
    readConfigFile(file);
}

ConfParser::~ConfParser()
{
    this->_configFile.close();
}

void ConfParser::readConfigFile(std::string file)
{
    this->_configFile.open(file.c_str());

    if (!this->_configFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo de conf" << std::endl;
        return ;
    }

    std::string line;
    while (std::getline(this->_configFile, line))
    {
        std::cout << line << "\n";
    }
    std::cout << std::endl;
}

