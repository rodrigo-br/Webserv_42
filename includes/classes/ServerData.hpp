#ifndef SERVER_DATA_H
# define SERVER_DATA_H

# include <map>
# include <string>
# include <vector>
# include "classes/Location.hpp"

class ServerData
{
    private:
        std::string _root;
        std::map<std::string, Location> _location;

    public:
        ServerData();

        std::string getRoot() const;
        std::string getLocation(std::string locationName) const;
        std::map<std::string, Location> getLocations() const;
        void setRoot(std::string root);
        void setLocation(std::string path, Location location);
        void setConfiguration(std::vector<std::string> tokens);
};

#endif
