#ifndef VALID_CONFIGURATIONS_H
# define VALID_CONFIGURATIONS_H

# include <iostream>
# include <string>
# include <map>

class IValidateFunction
{
    public:
        virtual void operator()(const std::string &) const = 0;
        virtual ~IValidateFunction() {}
};

template <typename T>
class ValidateFunction : public IValidateFunction
{
    private:
        T _value;

    public:
        ValidateFunction(T value) : _value(value) {}

        virtual void operator()(const std::string &str) const
        {
            // Parse the value and return a boolean for this operator
            std::cout << "Received: " << str << " " << this->_value << std::endl;
        }
};

class ValidConfigurations
{
    private:
        std::map<std::string, IValidateFunction*> _serverConfigurations;
        std::map<std::string, IValidateFunction*> _locationConfigurations;

    public:
        ValidConfigurations();
};

#endif
