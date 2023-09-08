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

char* PostMethod::generateResponsePage(const std::string& fileName)
{
    std::stringstream responseStream;
    responseStream << "<!DOCTYPE html>\n"
                    << "<html>\n"
                    << "<head>\n"
                    << "    <meta charset='UTF-8'>\n"
                    << "    <title>Upload Response</title>\n"
                    << "    <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@1/css/pico.min.css\">\n"
                    << "    <style>"
                    << "     body {"
                    << "            margin: 20px; /* Margem ao redor do conteúdo */"
                    << "            display: flex;"
                    << "            flex-direction: column;"
                    << "            align-items: center;"
                    << "            padding-top: 30px; /**/"
                    << "        }"
                    << "        h1, h3, p {"
                    << "            text-align: center;"
                    << "        }"
                    << "    </style>"
                    << "</head>\n"
                    << "<body>\n"
                    << "    <h1>Upload</h1>\n"
                    << "    <h3>O arquivo " << fileName << " foi adicionado com sucesso!</h3>\n"
                    << "    <p>Confira a pasta wwwroot/post e poderá ver o seu dog (ou seja lá o que tenha adicionado)!</p>\n"
                    << "</body>\n"
                    << "</html>\n";

    std::string responsePage = responseStream.str();
    this->_bodySize = responseStream.str().length() ;
    char* listingCStr = new char[_bodySize + 1];
    strcpy(listingCStr, responseStream.str().c_str());
    this->statusCode = StatusCodesEnum::OK;
    return listingCStr;
}


char *PostMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    char *body;
    std::string file;

    if (!this->validator.getMethodAllowed() && this->validator.getPath() == true)
    {
        file = this->root + std::string("/405.html");
        this->statusCode = StatusCodesEnum::METHOD_NOT_ALLOWED;
    }
    else if (this->validator.getBodySizeLimit() == false)
    {
        file = this->root + std::string("/413.html");
        this->statusCode = StatusCodesEnum::PAYLOAD_TOO_LARGE;
    }
    else if (request.getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
    {
        file = request.getBody();
        std::string filePath = this->root + "/post/" + request.getFileName();
        std::ofstream outFile(filePath.c_str(), std::ios::binary);
        if (outFile)
        {
            std::cout <<   "outFile = " << outFile << std::endl;
            outFile.write(file.c_str(), request.getBody().length());
            outFile.close();
            file = this->root + std::string("/post/success.html");
            this->statusCode = StatusCodesEnum::OK;
        }
        else
        {
            file = this->root + std::string("/post/error.html");
        }
    }
    else
    {
        file = this->root + std::string("/413.html");
        this->statusCode = StatusCodesEnum::LENGTH_REQUIRED;
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
    return body;
}

