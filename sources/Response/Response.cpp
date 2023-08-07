#include "classes/Response.hpp"

Response::Response(ResponseBuilder *builder) : _builder(builder), _response(NULL), _body(NULL)
{
    this->_response = _builder->build_response();
    this->_body = _builder->build_body();
    this->_size = std::strlen(this->_response);
}

Response::~Response()
{
    if (this->_response != NULL)
    {
        delete[] this->_response;
    }
    if (this->_body != NULL)
    {
        delete[] this->_body;
    }
    delete this->_builder;
}

const char *Response::get_body()
{
    return this->_body;
}

bool Response::has_body() const
{
    return this->_builder->has_body();
}

ssize_t Response::body_size() const
{
    return this->_builder->get_body_size();
}

const char *Response::get_response() const
{
    return this->_response;
}

size_t Response::get_size() const
{
    return this->_size;
}
