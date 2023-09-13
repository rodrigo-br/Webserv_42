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

std::string PostMethod::build_headers()
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");
    return headers;
}

std::string PostMethod::get_content_type()
{
    std::string file;
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else
    {
        file = this->root + this->validator.getErrorPage(404);
    }
    return this->_contentTypes.getMimeType(this->getExtension(file));
}

std::string PostMethod::get_status_msg() const
{
    return this->_statusCodes.getStatusMessage(this->get_status_code());
}

std::string  PostMethod::generateResponseBody( std::string fileName)
{
    std::string file = request.getBody();;
    if (!file.empty())
    {
        std::string filePath = this->root + "/post/" + fileName;
        std::ofstream outFile(filePath.c_str(), std::ios::binary);
        if (outFile)
        {
            outFile << file;
            outFile.close();
            file = this->root + std::string("/post/success.html");
            this->statusCode = StatusCodesEnum::OK;
        }
    }
    else
    {
        file = this->root + std::string("/post/error.html");
        this->statusCode = StatusCodesEnum::BAD_REQUEST;
    }
    return file;
}

char *PostMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    char *body;
    std::string file;

    if (!this->validator.getMethodAllowed() && (this->validator.getPath() || this->validator.isDirectoryListing()))
    {
        file = this->root + this->validator.getErrorPage(405);
        this->statusCode = StatusCodesEnum::METHOD_NOT_ALLOWED;
    }
    else if (!this->validator.getPath() && !this->validator.isDirectoryListing())
    {
        file = this->root + this->validator.getErrorPage(404);
        this->statusCode = StatusCodesEnum::NOT_FOUND;
    }
    else if (this->validator.getBodySizeLimit() == false)
    {
        file = this->root + this->validator.getErrorPage(413);
        this->statusCode = StatusCodesEnum::PAYLOAD_TOO_LARGE;
    }
    else if (request.getHeader("Content-Type").find("multipart/form-data") != std::string::npos && this->validator.getPath())
    {
        file = generateResponseBody( request.getFileName());
    }
    else if (request.getHeader("Transfer-Encoding") == "chunked" && this->validator.getPath())
    {
        file = generateResponseBody("temp_chunked_body.txt");
    }
    else if (request.getContentLength() == 0)
    {
        file = this->root + this->validator.getErrorPage(411);
        this->statusCode = StatusCodesEnum::LENGTH_REQUIRED;
    }
    else
    {
        file = this->root + this->validator.getErrorPage(501);
        this->statusCode = StatusCodesEnum::INTERNAL_SERVER_ERROR;
    }
    if(!file.empty())
    {
        std::vector<char> buffer = this->openFileAsVector(file);
        this->_bodySize = buffer.size();
        body = new char[this->_bodySize];
        std::copy(buffer.begin(), buffer.end(), body);
    }
    if (this->_bodySize > 0)
    {
        this->_hasBody = true;
    }
    if (this->isErrorFile(file))
    {
        this->statusCode = (StatusCodesEnum::statusCodes)this->findStatusCodeFromFile(file);
    }
    return body;
}

