#ifndef SERVER_DATA_H
# define SERVER_DATA_H

# include <map>
# include <string>
# include <vector>
# include "classes/Location.hpp"
# include <cstdlib>

class ServerData
{
    private:
        std::string _root;
        std::map<std::string, Location> _location;
        std::map<std::string, void (ServerData::*)(std::string)> _configurations;
        std::string _currentLocation;
        std::vector<std::string> _serverNames;

    public:
        ServerData();

        std::string getRoot() const;
        std::string getLocation(std::string locationName) const;
        std::vector<std::string> getServerNames() const;
        std::map<std::string, Location> getLocations() const;
        void setRoot(std::string root);
        void setLocation(std::string path, Location location);
        void setConfiguration(std::vector<std::string> tokens);
        void setLocationIndex(std::string index);
        void setLocationAllowedMethods(std::string allowedMethods);
        void setLocationDirectoryListening(std::string directoryListening);
        void setServerNames(std::string directoryListening);
};

#endif
