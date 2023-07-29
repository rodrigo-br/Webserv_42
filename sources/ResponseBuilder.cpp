#include "classes/ResponseBuilder.hpp"
#include <sstream> // Precisa ficar neste arquivo para evitar erro de incomplete type no test (C++11)

const char* ResponseBuilder::build_response()
{
    std::string response;

    // Opening Line
    response.append(this->get_protocol_version());
    response.append(" ");
    response.append(this->get_status_code());
    response.append(" ");
    response.append(this->get_status_msg());
    response.append("\r\n");

    // Headers
    response.append("Content-Type: ");
    response.append(this->get_content_type());
    response.append("\r\n\n");

    // convert string to char ptr
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());

    return response_as_char;
}

std::string ResponseBuilder::get_protocol_version() const
{
    return "HTTP/1.1";
}

std::string ResponseBuilder::get_status_code() const
{
    std::stringstream ss_code;
    ss_code << StatusCodesEnum::OK;
    return ss_code.str();
}

std::string ResponseBuilder::get_status_msg() const
{
    return statusCodes.get_status_message(this->get_status_code());
}

std::string ResponseBuilder::get_content_type() const
{
    return contentTypes.get_mime_type(".png");
}

