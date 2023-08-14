#include "classes/Location.hpp"

Location::Location()
{
}

Location::Location(std::string index, int allowedMethods, bool directoryListening) :
    _index(index), _allowedMethods(allowedMethods), _directoryListening(directoryListening)
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
        this->_index = rhs.getIndex();
    }
    return *this;
}

std::string Location::getIndex(void) const
{
    return this->_index;
}

int Location::getAllowedMethods(void) const
{
    return this->_allowedMethods;
}

bool Location::directoryListening(void) const
{
    return this->_directoryListening;
}