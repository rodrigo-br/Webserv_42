#include "interfaces/GetMethod.hpp"
#include <sstream> // Precisa ficar neste arquivo para evitar erro de incomplete type no test (C++11)

#define ROOT "wwwroot"

const char* GetMethod::buildResponse()
{
    std::string response;

    // Opening Line
    response.append(this->build_start_line());

    // Headers
    response.append(this->build_headers());

    // convert string to char ptr
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());

    return response_as_char;
}

const char* GetMethod::buildBody()
{
    return this->BODY_BUILDER_BIIIIHHHHLLL();
}

ssize_t GetMethod::getbodySize() const
{
    return this->_bodySize;
}

bool GetMethod::hasBody() const
{
    return this->_hasBody;
}

std::string GetMethod::build_start_line() const
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

std::string GetMethod::build_headers() const
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");

    return headers;
}

char *GetMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    std::string file;
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else
    {
        file = ROOT + std::string("/404.html");
    }
    std::vector<char> buffer = this->openFileAsVector(file);

    this->_bodySize = buffer.size();
    char *body = new char[this->_bodySize];
    std::copy(buffer.begin(), buffer.end(), body);

    if (this->_bodySize > 0)
    {
        this->_hasBody = true;
    }
    return body;
}

std::string GetMethod::get_status_code() const
{
    std::stringstream ss_code;
    ss_code << StatusCodesEnum::OK;
    return ss_code.str();
}

std::string GetMethod::get_status_msg() const
{
    return this->_statusCodes.getStatusMessage(this->get_status_code());
}

std::string GetMethod::get_content_type() const
{
    std::string file;
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else
    {
        file = ROOT + std::string("/404.html");
    }
    return this->_contentTypes.getMimeType(this->getExtension(file));
}
