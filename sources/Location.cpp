#include "classes/Location.hpp"

Location::Location()
{
}

Location::Location(std::string index) : _index(index)
{
}

Location::Location(Location const& src)
{
    *this = src;
}

Location& Location::operator=(Location const& rhs)
{
    if (this != &rhs)
    {
        this->_index = rhs.get_index();
    }
    return *this;
}

std::string Location::get_index(void) const
{
    return this->_index;
}

