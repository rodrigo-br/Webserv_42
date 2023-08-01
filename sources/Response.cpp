#include "classes/Response.hpp"

Response::Response()
{
    this->response = builder.build_response();
    this->size = std::strlen(response);
}

Response::~Response()
{
    if (this->response != NULL)
    {
        delete[] this->response;
    }
}

const char *Response::get_body()
{
    return this->builder.get_body();
}

bool Response::has_body() const
{
    return this->builder.has_body();
}

ssize_t Response::body_size() const
{
    return this->builder.get_body_size();
}

const char *Response::get_response() const
{
    return this->response;
}

size_t Response::get_size() const
{
    return this->size;
}
