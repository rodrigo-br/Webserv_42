#include "interfaces/MethodCreator.hpp"

IMethod *MethodCreator::create_method_object(HttpMethodEnum::httpMethod method)
{
    if (method == HttpMethodEnum::GET)
    {
        return new GetMethod();
    }
    else if (method == HttpMethodEnum::POST)
    {
        return new PostMethod();
    }
    else if (method == HttpMethodEnum::DELETE)
    {
        return new DeleteMethod();
    }
    return new UnknownMethod();
}

