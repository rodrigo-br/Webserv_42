#include "interfaces/MethodsFactory/Methods/UnknownMethod.hpp"

const char* UnknownMethod::buildResponse()
{
    std::string response;

    response.append(this->build_start_line());
    response.append(this->build_headers());
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());

    return response_as_char;
}

std::string UnknownMethod::build_start_line() const
{
    std::string start_line;
    start_line.append(this->getProtocolVersion());
    start_line.append(" ");
    start_line.append(this->get_status_code());
    start_line.append(" ");
    start_line.append(this->get_status_msg());
    start_line.append("\r\n");
    return start_line;
}

std::string UnknownMethod::build_headers()
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");
    return headers;
}

std::string UnknownMethod::get_content_type()
{
    std::string file = this->root + std::string(this->validator.getErrorPage(501));
    return this->_contentTypes.getMimeType(this->getExtension(file));
}

const char* UnknownMethod::buildBody()
{
    char * body;
    std::string file = this->root + this->validator.getErrorPage(501);
    this->statusCode = StatusCodesEnum::NOT_IMPLEMENTED;
    std::vector<char> buffer = this->openFileAsVector(file);
    this->_bodySize = buffer.size();
    body = new char[this->_bodySize];
    std::copy(buffer.begin(), buffer.end(), body);
    return body;
}

ssize_t UnknownMethod::getbodySize() const
{
    return this->_bodySize;
}

bool UnknownMethod::hasBody() const
{
    return true;
}

