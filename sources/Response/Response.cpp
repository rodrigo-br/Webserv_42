#include "classes/Response.hpp"

Response::Response() : response(NULL), body(NULL)
{
    this->response = builder.build_response();
    this->body = builder.build_body();
    this->size = std::strlen(response);
}

Response::~Response()
{
    if (this->response != NULL)
    {
        delete[] this->response;
    }
    if (this->body != NULL)
    {
        delete[] this->body;
    }
}

const char *Response::get_body()
{
    return this->body;
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
