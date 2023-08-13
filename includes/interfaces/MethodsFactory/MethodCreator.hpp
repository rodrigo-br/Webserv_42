#ifndef METHOD_CREATOR_H
# define METHOD_CREATOR_H

# include "interfaces/MethodsFactory/Methods/GetMethod.hpp"
# include "interfaces/MethodsFactory/Methods/PostMethod.hpp"
# include "interfaces/MethodsFactory/Methods/DeleteMethod.hpp"
# include "interfaces/MethodsFactory/Methods/UnknownMethod.hpp"
# include "enums/HttpMethodsEnum.hpp"

class MethodCreator
{
    public:
        static IMethod* createMethodObject(HttpMethodEnum::httpMethod method);
};

#endif
