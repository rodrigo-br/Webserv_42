#ifndef LOCATION_H
# define LOCATION_H

# include <string>

class Location
{
    private:
        std::string _index;
        int         _allowedMethods;
        bool        _directoryListening;

    public:
        Location();
        Location(std::string index, int allowedMethods=1, bool directoryListening=true);
        Location(Location const &src);
        Location    &operator=(Location const &rhs);
        std::string getIndex(void) const;
        int         getAllowedMethods(void) const;
        bool        getDirectoryListening(void) const;
        void        setIndex(std::string index);
        void        setAllowedMethods(int allowedMethods);
        void        setDirectoryListening(bool directoryListening);
};

#endif
