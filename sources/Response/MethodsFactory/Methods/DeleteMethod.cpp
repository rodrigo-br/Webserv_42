#include "interfaces/MethodsFactory/Methods/DeleteMethod.hpp"
#include <sstream> 

#define ROOT "wwwroot"

const char* DeleteMethod::buildResponse()
{
    std::string response;

    response.append(this->build_start_line());
    response.append(this->build_headers());
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());
    return response_as_char;
}

const char* DeleteMethod::buildBody()
{
    return BODY_BUILDER_BIIIIHHHHLLL();
}

ssize_t DeleteMethod::getbodySize() const
{
    return this->_bodySize;
}

bool DeleteMethod::hasBody() const
{
    return this->_hasBody;
}

std::string DeleteMethod::build_start_line() const
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

std::string DeleteMethod::build_headers() const
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");
    return headers;
}

bool containsUploadsFolder(const std::string& path) 
{
    size_t found = path.find("/uploads");
    return found != std::string::npos;
}

char *DeleteMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    std::string file;
    char        *body;
    std::string path = request.getPath();

    if (!this->validator.getMethodAllowed() && this->validator.getPath() == true)
    {
        file = this->root + std::string("/405.html");
        this->statusCode = StatusCodesEnum::METHOD_NOT_ALLOWED;
    }
    else if (path.find("/delete") != std::string::npos) 
    {
        const char* filePath = path.c_str();
		if (remove(filePath) == 0)
        {
            this->statusCode = StatusCodesEnum::OK;
            std::cout <<  "äaaaaaaaaaaaaaaa" << std::endl;
        }
        else
        {   
            this->statusCode = StatusCodesEnum::NOT_IMPLEMENTED;
            file = this->root + std::string("/404.html");
        }
    }
    if (!file.empty())
    {
        std::vector<char> buffer = this->openFileAsVector(file);
        this->_bodySize = buffer.size();
        body = new char[this->_bodySize];
        std::copy(buffer.begin(), buffer.end(), body);
    }
    else
    {
        std::ostringstream responseDelete;
        std::string responseBody = responseDelete.str();
        this->_bodySize = responseBody.size();
        body = new char[this->_bodySize];
        std::strcpy(body, responseBody.c_str()); 
    }
    if (this->_bodySize > 0)
    {
        this->_hasBody = true;
    }
    return  body;
}

std::string DeleteMethod::get_content_type() const
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

std::string DeleteMethod::get_status_msg() const
{
    return this->_statusCodes.getStatusMessage(this->get_status_code());
}
    