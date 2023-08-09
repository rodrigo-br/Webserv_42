#include "classes/ResponseBuilder.hpp"

ResponseBuilder::ResponseBuilder(Request &request, RequestValidator &validator)
{
    this->_method = MethodCreator::createMethodObject(validator.getMethod());
    this->_method->request = request;
    this->_method->validator = validator;
}

ResponseBuilder::~ResponseBuilder()
{
    delete this->_method;
}

const char* ResponseBuilder::buildResponse()
{
    return this->_method->buildResponse();
}

const char* ResponseBuilder::buildBody()
{
    return this->_method->buildBody();
}

ssize_t ResponseBuilder::getbodySize() const
{
    return this->_method->getbodySize();
}

bool ResponseBuilder::hasBody() const
{
    return this->_method->hasBody();
}

