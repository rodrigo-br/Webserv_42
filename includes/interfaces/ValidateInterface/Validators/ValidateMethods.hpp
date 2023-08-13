#ifndef VALIDATE_METHODS_H
# define VALIDATE_METHODS_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"

class ValidateMethods : public IValidateFunction
{
    public:
        ValidateMethods() {};

        virtual bool operator()(std::string &input) const
        {
            int methodsCode = std::atoi(input.c_str());
            return (methodsCode >= 1 && methodsCode <= 7);
        }
};

#endif
