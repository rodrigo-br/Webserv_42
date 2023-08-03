#include "interfaces/DeleteMethod.hpp"

const char* DeleteMethod::build_response()
{
    return NULL;
}

const char* DeleteMethod::build_body()
{
    return NULL;
}

ssize_t DeleteMethod::get_body_size() const
{
    return 0;
}

bool DeleteMethod::has_body() const
{
    return false;
}

