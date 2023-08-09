#include "interfaces/DeleteMethod.hpp"

const char* DeleteMethod::buildResponse()
{
    return NULL;
}

const char* DeleteMethod::buildBody()
{
    return NULL;
}

ssize_t DeleteMethod::getbodySize() const
{
    return 0;
}

bool DeleteMethod::hasBody() const
{
    return false;
}

