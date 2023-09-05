#include "interfaces/MethodsFactory/Methods/PostMethod.hpp"
#include <sstream> 
# include <vector>
# include <iostream>
# include <fstream>
const char* PostMethod::buildResponse()
{
    std::string response;

    response.append(this->build_start_line());
    response.append(this->build_headers());
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());
    return response_as_char;
}

const char* PostMethod::buildBody()
{
    return this->BODY_BUILDER_BIIIIHHHHLLL();
}

ssize_t PostMethod::getbodySize() const
{
    return this->_bodySize;
}

bool PostMethod::hasBody() const
{
    return this->_hasBody;
}

std::string PostMethod::build_start_line() const
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

std::string PostMethod::build_headers() const
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");
    return headers;
}

std::string PostMethod::get_status_code() const
{
    std::stringstream ss_code;
    ss_code << StatusCodesEnum::OK;
    return ss_code.str();
}

std::string PostMethod::get_content_type() const
{
    std::string file;
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else
    {
        file = this->root + std::string("/404.html");
    }
    return this->_contentTypes.getMimeType(this->getExtension(file));
}

std::string PostMethod::get_status_msg() const
{
    return this->_statusCodes.getStatusMessage(this->get_status_code());
}

char *PostMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    char *body;

    if (request.getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
    {
        std::string fileContent = request.getBody();
        std::string filePath = "wwwroot/post/" + request.getFileName();
        std::ofstream outFile(filePath.c_str(), std::ios::binary);
        if (outFile)
        {
            outFile.write(fileContent.c_str(), request.getBody().length());
            outFile.close();
        }
        else
        {
            std::cout << std::endl <<  "error =====  " << fileContent << std::endl << std::endl;

        }
        this->_bodySize = fileContent.size();
        body = new char[this->_bodySize];
        memcpy(body, fileContent.c_str(), this->_bodySize);

    }
    else
    {
        std::cout << "DEU RUIM " << request.getHeader("Content-Type") << std::endl;
    }

    if (this->_bodySize > 0)
    {
        this->_hasBody = true;
    }
    return body;
}

