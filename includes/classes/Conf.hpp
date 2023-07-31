#ifndef CONF_H
# define CONF_H

# include <map>
# include <string>

class Conf
{
    private:
        int listen;
        std::string root;
        std::map<std::string, std::string> location;

    public:
        Conf();

        int get_listen() const;
        std::string get_root() const;
        std::map<std::string, std::string> get_locations() const;
};

#endif
