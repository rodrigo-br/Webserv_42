#ifndef VALIDATE_DIRECTORY_LISTING_INDEX_H
# define VALIDATE_DIRECTORY_LISTING_INDEX_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include <string>

class ValidateGenericConfiguration : public IValidateFunction
{
    private:
        std::string _expected;

    public:
        ValidateGenericConfiguration(std::string expected) : _expected(expected) {};

        virtual bool operator()(std::string &input) const
        {
            return input.compare(this->_expected) == 0;
        }
};

#endif
