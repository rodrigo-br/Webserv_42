#include "Response.hpp"

Response::Response()
{
    build_response();
}

void Response::build_response()
{
    this->response = "HTTP/1.1 200 OK\nContent-Type: image/png\n\n";
    this->size = this->response.size();
}

std::string Response::get_response() const
{
    return this->response;
}

size_t Response::get_size() const
{
    return this->size;
}
