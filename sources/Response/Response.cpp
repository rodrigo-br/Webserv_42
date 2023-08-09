#include "classes/Response.hpp"

Response::Response(ResponseBuilder *builder) : _builder(builder), _response(NULL), _body(NULL)
{
    this->_response = _builder->buildResponse();
    this->_body = _builder->buildBody();
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

const char *Response::getBody()
{
    return this->_body;
}

bool Response::hasBody() const
{
    return this->_builder->hasBody();
}

ssize_t Response::bodySize() const
{
    return this->_builder->getbodySize();
}

const char *Response::getResponse() const
{
    return this->_response;
}

size_t Response::getSize() const
{
    return this->_size;
}
