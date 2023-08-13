#ifndef VALID_CONFIGURATIONS_H
# define VALID_CONFIGURATIONS_H

# include <iostream>
# include <string>
# include <map>
# include <set>
# include <cstdlib>
# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include "interfaces/ValidateInterface/Validators/ValidatePortIsSafe.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateDirectoryExist.hpp"

template <typename T>
class ValidateFunction : public IValidateFunction
{
    private:
        T _value;

    public:
        ValidateFunction(T value) : _value(value) {}

        virtual bool operator()(std::string &str) const
        {
            (void)str;
            return true;
        }
};

class ValidConfigurations
{
    private:
        std::map<std::string, IValidateFunction*> _serverConfigurations;
        std::map<std::string, IValidateFunction*> _locationConfigurations;

    public:
        ValidConfigurations();
        ~ValidConfigurations();
        bool ValidateAServerConfiguration(std::string &key, std::string &value);
};

#endif
