#ifndef IMETHOD_H
# define IMETHOD_H

# include "interfaces/MethodsUtils.hpp"
# include "classes/Request.hpp"
# include "classes/RequestValidator.hpp"

class IMethod : public MethodsUtils
{
    public:
        Request request;
        RequestValidator validator;
        virtual ~IMethod() {};

        virtual const char  *buildResponse() = 0;
        virtual const char  *buildBody() = 0;
        virtual ssize_t     getbodySize() const = 0;
        virtual bool        hasBody() const = 0;
};

#endif
