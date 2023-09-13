#include "classes/Location.hpp"

Location::Location() : _index(""), _allowedMethods(0), _directoryListening(false), _isRedirect(false)
{
}

Location::Location(std::string index, int allowedMethods, bool directoryListening, bool isRedirect) :
    _index(index), _allowedMethods(allowedMethods), _directoryListening(directoryListening), _isRedirect(isRedirect)
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
        this->_allowedMethods = rhs.getAllowedMethods();
        this->_directoryListening = rhs.getDirectoryListening();
        this->_isRedirect = rhs.getIsRedirect();
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

void         Location::setIsRedirect()
{
    this->_isRedirect = true;
}

bool         Location::getIsRedirect() const
{
    return  this->_isRedirect;
}