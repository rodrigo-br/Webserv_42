#include "classes/ResponseBuilder.hpp"

ResponseBuilder::ResponseBuilder()
{
    this->method = MethodCreator::create_method_object(HttpMethodEnum::GET);
}

ResponseBuilder::~ResponseBuilder()
{
    delete this->method;
}

const char* ResponseBuilder::build_response()
{
    return this->method->build_response();
}

const char* ResponseBuilder::build_body()
{
    return this->method->build_body();
}

ssize_t ResponseBuilder::get_body_size() const
{
    return this->method->get_body_size();
}

bool ResponseBuilder::has_body() const
{
    return this->method->has_body();
}

