#ifndef CONF_H
# define CONF_H

# include <map>
# include <string>
# include "classes/Location.hpp"
# include "classes/ConfParser.hpp"

class Conf
{
    private:
        int                             _listen;
        std::string                     _root;
        std::map<std::string, Location> _location;
        ConfParser                      *_parser;

    public:
        Conf(ConfParser *parser);

        bool succeeded();
        void deleteConfParser();
        int get_listen() const;
        std::string get_root() const;
        std::string get_locations( std::string location_name ) const;
        std::map<std::string, Location> get_locations() const;

};

#endif
