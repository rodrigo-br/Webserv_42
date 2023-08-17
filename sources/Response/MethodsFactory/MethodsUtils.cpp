#include "interfaces/MethodsFactory/MethodsUtils.hpp"
#include <sstream>

# define ROOT "wwwroot/"

std::vector<char> MethodsUtils::openFileAsVector(std::string path)
{
    if (path == ROOT)
    {
        path += "index.html";
    }
    else if (path ==  "/cgi-bin")
    {
        path = "wwwroot" + path + "/index.py";
    }
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cout << "Failed to open file " << path << std::endl;
        return std::vector<char>();
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> imageBuffer(size);
    if (!file.read(imageBuffer.data(), size))
    {
        std::cout << "Failed to read image file" << std::endl;
        return std::vector<char>();
    }
    file.close();

    return imageBuffer;
}

std::string MethodsUtils::getExtension(std::string path) const
{
    if (path == ROOT)
    {
        path += "index.html";
    }
    else if (path ==  "/cgi-bin")
    {
        path = "wwwroot" + path + "/index.py";
    }
    size_t pos = path.find_last_of('.');
    if (pos == std::string::npos)
    {
        return (".bin");
    }
    return path.substr(pos);
}

std::string MethodsUtils::getProtocolVersion() const
{
    return "HTTP/1.1";
}
