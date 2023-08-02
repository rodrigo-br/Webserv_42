#include "interfaces/GetMethod.hpp"
#include <sstream> // Precisa ficar neste arquivo para evitar erro de incomplete type no test (C++11)

const char* GetMethod::build_response()
{
    std::string response;

    // Opening Line
    response.append(this->build_start_line());

    // Headers
    response.append(this->build_headers());

    // ssize_t body_size;
    // Body
    // response.append(this->BODY_BUILDER_BIIIIHHHHLLL(body_size));

    // convert string to char ptr
    char *response_as_char = new char[(response.length() + 1)];
    std::strcpy(response_as_char, response.c_str());

    // std::cout << response_as_char << std::endl;

    return response_as_char;
}

const char* GetMethod::build_body()
{
    return this->BODY_BUILDER_BIIIIHHHHLLL();
}

ssize_t GetMethod::get_body_size() const
{
    return this->body_size;
}

bool GetMethod::has_body() const
{
    return this->hasBody;
}

std::string GetMethod::build_start_line() const
{
    std::string start_line;
    start_line.append(this->get_protocol_version());
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
    std::ifstream file("files/Dogs.png", std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cout << "Failed to open image file." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> imageBuffer(size);
    if (!file.read(imageBuffer.data(), size))
    {
        std::cout << "Failed to read image file" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();

    this->body_size = imageBuffer.size();
    char *body = new char[this->body_size];
    std::copy(imageBuffer.begin(), imageBuffer.end(), body);

    if (this->body_size > 0)
    {
        this->hasBody = true;
    }
    return body;
}

std::string GetMethod::get_protocol_version() const
{
    return "HTTP/1.1";
}

std::string GetMethod::get_status_code() const
{
    std::stringstream ss_code;
    ss_code << StatusCodesEnum::OK;
    return ss_code.str();
}

std::string GetMethod::get_status_msg() const
{
    return statusCodes.get_status_message(this->get_status_code());
}

std::string GetMethod::get_content_type() const
{
    return contentTypes.get_mime_type(".png");
}
