#ifndef CONF_PARSER_H
# define CONF_PARSER_H

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstring>
# include <cstdlib>
# include "interfaces/ValidateInterface/ValidConfigurations.hpp"
# include "classes/ServerData.hpp"

class ConfParser
{
    public:
        ConfParser(std::string file);
        ~ConfParser();
        bool succeed();

    private:
        std::ifstream                   _configFile;
        bool                            _succeed;
        bool                            _inServerBrackets;
        bool                            _inLocationBrackets;
        ValidConfigurations             _validConfigurations;
        std::map<int, ServerData>       _serversData;
        int                             _currentServerConfig;

        void readConfigFile(std::string file);
        void createServers();
        bool assignTokens(std::vector<std::string> tokens);
        bool isValidClosingBracket(std::string token);
        bool isValidConfiguration(std::vector<std::string> tokens);
        void createOrUpdateServerData(std::vector<std::string> tokens);
};

#endif
