#include "interfaces/UnknownMethod.hpp"

const char* UnknownMethod::build_response()
{
    return NULL;
}

const char* UnknownMethod::build_body()
{
    return NULL;
}

ssize_t UnknownMethod::get_body_size() const
{
    return 0;
}

bool UnknownMethod::has_body() const
{
    return false;
}

