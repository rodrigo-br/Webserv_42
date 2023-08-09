#ifndef METHOD_CREATOR_H
# define METHOD_CREATOR_H

# include "interfaces/GetMethod.hpp"
# include "interfaces/PostMethod.hpp"
# include "interfaces/DeleteMethod.hpp"
# include "interfaces/UnknownMethod.hpp"
# include "enums/HttpMethodsEnum.hpp"

class MethodCreator
{
    public:
        static IMethod* createMethodObject(HttpMethodEnum::httpMethod method);
};

#endif
