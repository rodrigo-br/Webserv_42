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

const char *Response::get_response() const
{
    return this->response;
}

size_t Response::get_size() const
{
    return this->size;
}
