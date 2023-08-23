#ifndef VALIDATE_SERVER_NAMES_H
# define VALIDATE_SERVER_NAMES_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include <string>

class ValidateServerNames : public IValidateFunction
{
    private:

    public:
        ValidateServerNames() {};

        virtual bool operator()(std::string &input) const
        {
            return (input.find("..") == std::string::npos &&
                    input.find("/") == std::string::npos &&
                    input.find("\\") == std::string::npos &&
                    input.find("\"") == std::string::npos &&
                    input.find("\'") == std::string::npos &&
                    input.find("*") == std::string::npos &&
                    input.find("!") == std::string::npos &&
                    input.find("@") == std::string::npos &&
                    input.find("#") == std::string::npos &&
                    input.find("$") == std::string::npos &&
                    input.find("%") == std::string::npos &&
                    input.find("¨") == std::string::npos &&
                    input.find("&") == std::string::npos &&
                    input.find("(") == std::string::npos &&
                    input.find(")") == std::string::npos
            );
        }
};

#endif
