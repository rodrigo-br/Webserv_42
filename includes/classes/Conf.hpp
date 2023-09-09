#ifndef CONF_H
# define CONF_H

# include <map>
# include <string>
# include "classes/Location.hpp"
# include "classes/ConfParser.hpp"
# include "classes/ServerData.hpp"

class Conf
{
    private:
        std::string                      _root;
        std::map<std::string, Location>  _location;
        ConfParser                       *_parser;

    public:
        Conf(ConfParser *parser);

        bool succeeded();
        void deleteConfParser();
        std::string getRoot(int port) const;
        std::string getLocation(int port, std::string locationName) const;
        std::map<std::string, Location> getLocations(int port) const;
        std::map<int, ServerData> &getServersData();
        bool criticalError();
};

#endif
