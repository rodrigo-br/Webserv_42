#include "interfaces/MethodsFactory/Methods/PostMethod.hpp"
#include <sstream> 

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

// char *PostMethod::BODY_BUILDER_BIIIIHHHHLLL()
// {
//     char *body;
//     if (request.getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
//     {
//         std::ostringstream responseDelete;
//         responseDelete << "HTTP/1.1 200 OK\r\n";
//         responseDelete << "\r\n";

//         std::string responseBody = responseDelete.str();

//         std::ifstream fileStream(request.getPath().c_str(), std::ios::binary);
//         if (fileStream) 
//         {
//             std::ostringstream fileContentStream;
//             fileContentStream << fileStream.rdbuf();
//             responseBody += fileContentStream.str();
//             fileStream.close();
//         } 
//         else 
//         {
//             responseBody += "Failed to read file content.";
//         }

//         this->_bodySize = responseBody.size();
//         body = new char[this->_bodySize + 1];
//         std::strcpy(body, responseBody.c_str());
//         body[this->_bodySize] = '\0';
//         std::cout <<  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa = " << body << std::endl;


//     }
//     else 
//     {
//         std::cout <<  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa = " << request.getHeader("Content-Type") << std::endl;
//     }

//     if (this->_bodySize > 0)
//     {
//         this->_hasBody = true;
//     }
//     return body;
// }

    char *PostMethod::BODY_BUILDER_BIIIIHHHHLLL()
    {
        char *body;

        if (request.getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
        {
            std::ostringstream responseStream;
            responseStream << "HTTP/1.1 200 OK\r\n";
            responseStream << "Content-Type: text/html\r\n";
            responseStream << "\r\n";

            std::string responseBody = responseStream.str();
            std::string fileName = request.getBody();
            size_t filenamePos = fileName.find("filename=\"");
            if (filenamePos != std::string::npos) 
            {
                fileName = fileName.substr(filenamePos + 10);
                fileName = fileName.substr(0, fileName.find("\""));
            }
        
            std::string fileContent;
            std::string filePath = "wwwroot/post/" + fileName;
            std::cout << std::endl <<  "filePath =====  " << filePath << std::endl << std::endl;
            std::ofstream outFile(filePath.c_str(), std::ios::binary);
            if (outFile)
            {
                outFile.write(fileContent.c_str(), fileContent.length());
                outFile.close();
                std::cout << std::endl <<  "fileContent =====  " << fileContent << std::endl << std::endl;
                responseBody += "File uploaded successfully.";
            }
            else
            {
                std::cout << std::endl <<  "error =====  " << fileContent << std::endl << std::endl;

                responseBody += "Failed to upload file. ";
            }
            this->_bodySize = responseBody.size();
            body = new char[this->_bodySize + 1];
            std::strcpy(body, responseBody.c_str());
            body[this->_bodySize] = '\0';
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

