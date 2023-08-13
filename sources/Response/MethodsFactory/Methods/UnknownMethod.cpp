#include "interfaces/MethodsFactory/Methods/UnknownMethod.hpp"

const char* UnknownMethod::buildResponse()
{
    return NULL;
}

const char* UnknownMethod::buildBody()
{
    return NULL;
}

ssize_t UnknownMethod::getbodySize() const
{
    return 0;
}

bool UnknownMethod::hasBody() const
{
    return false;
}

