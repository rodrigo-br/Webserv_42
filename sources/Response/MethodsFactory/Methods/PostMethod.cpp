#include "interfaces/PostMethod.hpp"

const char* PostMethod::buildResponse()
{
    return NULL;
}

const char* PostMethod::buildBody()
{
    return NULL;
}

ssize_t PostMethod::getbodySize() const
{
    return 0;
}

bool PostMethod::hasBody() const
{
    return false;
}

