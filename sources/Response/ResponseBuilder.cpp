#include "classes/ResponseBuilder.hpp"

ResponseBuilder::ResponseBuilder(Request &request, RequestValidator &validator)
{
    this->_method = MethodCreator::create_method_object(validator.get_method());
    this->_method->request = request;
}

ResponseBuilder::~ResponseBuilder()
{
    delete this->_method;
}

const char* ResponseBuilder::build_response()
{
    return this->_method->build_response();
}

const char* ResponseBuilder::build_body()
{
    return this->_method->build_body();
}

ssize_t ResponseBuilder::get_body_size() const
{
    return this->_method->get_body_size();
}

bool ResponseBuilder::has_body() const
{
    return this->_method->has_body();
}

