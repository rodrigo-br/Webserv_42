#ifndef CONF_H
# define CONF_H

# include <map>
# include <string>
# include "classes/Location.hpp"

class Conf
{
    private:
        int listen;
        std::string root;
        std::map<std::string, Location> location;

    public:
        Conf();

        int get_listen() const;
        std::string get_root() const;
        std::string get_locations( std::string location_name ) const;
        std::map<std::string, Location> get_locations() const;

};

#endif
