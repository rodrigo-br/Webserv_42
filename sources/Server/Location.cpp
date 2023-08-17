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

bool Location::getDirectoryListening(void) const
{
    return this->_directoryListening;
}

void Location::setIndex(std::string index)
{
    this->_index = index;
}

void Location::setAllowedMethods(int allowedMethods)
{
    this->_allowedMethods = allowedMethods;
}

void Location::setDirectoryListening(bool directoryListening)
{
    this->_directoryListening = directoryListening;
}

