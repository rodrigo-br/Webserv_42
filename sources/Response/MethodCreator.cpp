#include "interfaces/MethodCreator.hpp"

IMethod *MethodCreator::create_method_object(HttpMethodEnum::httpMethod method)
{
    switch(method)
    {
        case HttpMethodEnum::GET:
            return new GetMethod();
        case HttpMethodEnum::POST:
            return new PostMethod();
        case HttpMethodEnum::DELETE:
            return new DeleteMethod();
        default:
            return new UnknownMethod();
    }
}

