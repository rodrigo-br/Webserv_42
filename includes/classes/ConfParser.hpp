#ifndef CONF_PARSER_H
# define CONF_PARSER_H

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstring>
# include <cstdlib>

class ConfParser
{
    public:
        ConfParser(std::string file);
        ~ConfParser();
        bool succeed();

    private:
        std::ifstream _configFile;
        bool _succeed;

        void readConfigFile(std::string file);
        void createServers();
        bool assignTokens(std::vector<std::string> tokens);
};

#endif
