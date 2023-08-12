#include "classes/ConfParser.hpp"
#include <sstream>

ConfParser::ConfParser(std::string file) :
    _succeed(false), _inServerBrackets(false), _inLocationBrackets(false)
{
    readConfigFile(file);
    createServers();
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
}

void ConfParser::createServers()
{
    std::string line;
    while (std::getline(this->_configFile, line))
    {
        char *token = std::strtok(const_cast<char *>(line.c_str()), " \n");
        std::vector<std::string> tokens;
        if (token != NULL)
        {
            while (token != NULL)
            {
                tokens.push_back(token);
                token = std::strtok(NULL, " \n");
            }
            this->_succeed = assignTokens(tokens);
            if (tokens.size() > 0 && !this->_succeed)
            {
                break ;
            }
        }
    }
}

static bool isServerBlock(std::vector<std::string> tokens)
{
    return (tokens[0].compare("server") == 0) && (tokens[1].compare("{") == 0);
}

static bool isLocationBlock(std::vector<std::string> tokens)
{
    // Need to verify token[1] for a valid location path
    return (tokens[0].compare("location") == 0 && tokens[2].compare("{") == 0);
}

bool ConfParser::isValidClosingBracket(std::string token)
{
    if (token.compare("}") == 0)
    {
        if (this->_inLocationBrackets)
        {
            this->_inLocationBrackets = false;
            return true;
        }
        else if (this->_inServerBrackets)
        {
            this->_inServerBrackets = false;
            return true;
        }
    }
    return false;
}

bool ConfParser::assignTokens(std::vector<std::string> tokens)
{
    size_t tokensSize = tokens.size();
    if (tokensSize > 3 || tokensSize <= 0)
    {
        return false;
    }
    else if (tokensSize == 1)
    {
        return isValidClosingBracket(tokens[0]);
    }
    else if (tokensSize == 2)
    {
        if (isServerBlock(tokens))
        {
            this->_inServerBrackets = !this->_inServerBrackets;
            return this->_inServerBrackets;
        }
        // Need to check for valid configurations
        return (tokens[0].compare("location") != 0);
    }
    else if (tokensSize == 3)
    {
        if (isLocationBlock(tokens))
        {
            this->_inLocationBrackets = !this->_inLocationBrackets;
            return this->_inLocationBrackets;
        }
    }
    return false;
}

bool ConfParser::succeed()
{
    return this->_succeed;
}
