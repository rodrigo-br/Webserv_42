#include "interfaces/PostMethod.hpp"

const char* PostMethod::build_response()
{
    return NULL;
}

const char* PostMethod::build_body()
{
    return NULL;
}

ssize_t PostMethod::get_body_size() const
{
    return 0;
}

bool PostMethod::has_body() const
{
    return false;
}

