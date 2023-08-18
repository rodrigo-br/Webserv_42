#include "classes/ConfParser.hpp"
#include <sstream>

static bool notEmptyLineAndFailed(size_t size, bool succeed)
{
    return (size > 0) && !succeed;
}

static bool isServerBlock(std::vector<std::string> tokens)
{
    return (tokens[0].compare("server") == 0) && (tokens[1].compare("{") == 0);
}

bool ConfParser::isLocationBlock(std::vector<std::string> tokens)
{
    std::string value = this->_serversData[this->_currentServerConfig].getRoot() + tokens[1];
    return (tokens[0].compare("location") == 0 && tokens[2].compare("{") == 0
            && (this->_validConfigurations.ValidateAServerConfiguration(tokens[0],
            value) || tokens[1].compare("/") == 0));
}


void ConfParser::createOrUpdateLocationData(std::vector<std::string> tokens)
{
    this->_serversData[this->_currentServerConfig].setConfiguration(tokens);
}

static bool switchMe(bool &me)
{
    me = !me;
    return me;
}

void ConfParser::createOrUpdateServerData(std::vector<std::string> tokens)
{
    if (tokens[0].compare("listen") == 0)
    {
        this->_currentServerConfig = std::atoi(tokens[1].c_str());
        this->_serversData[this->_currentServerConfig] = ServerData();
    }
    this->_serversData[this->_currentServerConfig].setConfiguration(tokens);
}

bool ConfParser::isValidConfiguration(std::vector<std::string> tokens)
{
    if (tokens[0].compare("location") != 0)
    {
        if (this->_inServerBrackets && !this->_inLocationBrackets)
        {
            if (this->_validConfigurations.ValidateAServerConfiguration(tokens[0], tokens[1]))
            {
                createOrUpdateServerData(tokens);
                return true;
            }
        }
        else if (this->_inServerBrackets && this->_inLocationBrackets)
        {
            if (tokens[0].compare("index") == 0)
            {
                ServerData server = this->_serversData[this->_currentServerConfig];
                tokens[1] = server.getRoot() + this->_currentLocationBlock + "/" + tokens[1];
            }
            if (this->_validConfigurations.ValidateALocationConfiguration(tokens[0], tokens[1]))
            {
                createOrUpdateLocationData(tokens);
                return true;
            }
        }
    }
    return false;
}

ConfParser::ConfParser(std::string file) :
    _succeed(false), _inServerBrackets(false), _inLocationBrackets(false), _currentServerConfig(-1)
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
            if (notEmptyLineAndFailed(tokens.size(), this->_succeed))
            {
                std::cout << "Falhô" << std::endl;
                std::cout << tokens[0] << std::endl;
                break ;
            }
            if (this->_currentServerConfig > 0)
            {
                this->_serversData[this->_currentServerConfig].setConfiguration(tokens);
            }
        }
    }
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
            this->_currentServerConfig = -1;
            return true;
        }
    }
    return false;
}

bool ConfParser::assignTokens(std::vector<std::string> tokens)
{
    size_t tokensSize = tokens.size();
    switch(tokensSize)
    {
        case 1:
            return isValidClosingBracket(tokens[0]);
        case 2:
            if (isServerBlock(tokens))
            {
                return switchMe(this->_inServerBrackets);
            }
            return (isValidConfiguration(tokens));
        case 3:
            if (isLocationBlock(tokens))
            {
                this->_currentLocationBlock = tokens[1].compare("/") != 0 ? tokens[1] : "" ;
                return switchMe(this->_inLocationBrackets);
            }
            return false;
        default:
            return false;
    }
}

bool ConfParser::succeed()
{
    return this->_succeed;
}


std::string ConfParser::getRoot(int port) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getRoot();
    else
        throw std::invalid_argument("Porta não encontrada");
}

std::map<std::string, Location> ConfParser::getLocations(int port) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getLocations();
    else
        throw std::invalid_argument("Porta não encontrada");
}


std::map<int, ServerData>& ConfParser::getServersData()
{
    return this->_serversData;
}

std::string ConfParser::getLocation(int port, std::string locationName) const
{
    std::map<int, ServerData>::const_iterator it = this->_serversData.find(port);

    if (it != this->_serversData.end())
        return it->second.getLocation(locationName);
    else
        throw std::invalid_argument("Porta não encontrada");
}

