#ifndef CONF_PARSER_H
# define CONF_PARSER_H

# include <iostream>
# include <fstream>
# include <string>

class ConfParser
{
    public:
        ConfParser(std::string file);
        ~ConfParser();

    private:
        std::ifstream _configFile;

        void readConfigFile(std::string file);
};

#endif
