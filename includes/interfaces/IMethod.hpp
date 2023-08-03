#ifndef IMETHOD_H
# define IMETHOD_H

# include "MethodsUtils.hpp"

class IMethod : public MethodsUtils
{
    public:
        virtual ~IMethod() {};

        virtual const char  *build_response() = 0;
        virtual const char  *build_body() = 0;
        virtual ssize_t     get_body_size() const = 0;
        virtual bool        has_body() const = 0;
};

#endif
