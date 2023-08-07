#ifndef LOCATION_H
# define LOCATION_H

# include <string>

class Location
{
    private:
        std::string _index;

    public:
        Location();
        Location(std::string index);
        Location(Location const &src);
        Location    &operator=(Location const &rhs);
        std::string get_index(void) const;
};

#endif
