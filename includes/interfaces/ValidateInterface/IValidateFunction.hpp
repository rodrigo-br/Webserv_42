#ifndef IVALIDATE_FUNCTION_H
# define IVALIDATE_FUNCTION_H

class IValidateFunction
{
    public:
        virtual bool operator()(std::string &) const = 0;
        virtual ~IValidateFunction() {}
};

#endif
