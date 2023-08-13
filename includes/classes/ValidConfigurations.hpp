#ifndef VALID_CONFIGURATIONS_H
# define VALID_CONFIGURATIONS_H

# include <iostream>
# include <string>
# include <map>
# include <set>
# include <cstdlib>

class IValidateFunction
{
    public:
        virtual bool operator()(std::string &) const = 0;
        virtual ~IValidateFunction() {}
};

template <size_t N>
class ValidatePortIsSafe : public IValidateFunction
{
    private:
        int _unsafePorts[N];

    public:
        ValidatePortIsSafe(int (&unsafePorts)[N])
        {
            for (size_t i = 0; i < N; ++i)
            {
                _unsafePorts[i] = unsafePorts[i];
            }
        }

        virtual bool operator()(std::string &portInput) const
        {
            int port = std::atoi(portInput.c_str());
            if (_unsafePorts != NULL && (port != 0 || portInput == "0"))
            {
                if (port > 1024 && port < 49151)
                {
                    for (size_t i = 0; i < N; ++i)
                    {
                        if (port == _unsafePorts[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;

            // Parse the value and return a boolean for this operator
        }
};

template <typename T>
class ValidateFunction : public IValidateFunction
{
    private:
        T _value;

    public:
        ValidateFunction(T value) : _value(value) {}

        virtual bool operator()(const std::string &str) const
        {
            (void)str;
            return true;
            // Parse the value and return a boolean for this operator
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
