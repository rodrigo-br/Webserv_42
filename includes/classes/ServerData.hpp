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
        int _bodySizeLimit;
        std::string _currentLocation;
        std::vector<std::string> _serverNames;
        std::map<std::string, Location> _location;
        std::map<std::string, void (ServerData::*)(std::string)> _configurations;

    public:
        ServerData();

        std::string getRoot() const;
        int getBodySizeLimit() const;
        std::vector<std::string> getServerNames() const;
        std::map<std::string, Location> getLocations() const;
        std::string getLocation(std::string locationName) const;
        void setRoot(std::string root);
        void setBodySizeLimit(std::string value);
        void setLocationIndex(std::string index);
        void setServerNames(std::string directoryListening);
        void setLocation(std::string path, Location location);
        void setConfiguration(std::vector<std::string> tokens);
        bool isDirectoryListingLocation(std::string locationPath);
        void setLocationAllowedMethods(std::string allowedMethods);
        void setLocationDirectoryListening(std::string directoryListening);
};

#endif
