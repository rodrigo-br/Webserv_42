#include "classes/ConfParser.hpp"

ConfParser::ConfParser(std::string file)
{
    readConfigFile(file);
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
    this->_configFile.close();
}

