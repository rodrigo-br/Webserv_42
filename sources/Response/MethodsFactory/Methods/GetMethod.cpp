#include "interfaces/MethodsFactory/Methods/GetMethod.hpp"
#include <sstream> // Precisa ficar neste arquivo para evitar erro de incomplete type no test (C++11)
#include <dirent.h>

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


char *GetMethod::getDirectoryListing() 
{
    DIR *dir;
    struct dirent *ent;
    struct stat filestat;
    std::string fullFilePath, modifiedTime;
    std::string directoryPath = this->request.getPath();
    if (!directoryPath.empty() && directoryPath[directoryPath.length() - 1] != '/')
    {
        directoryPath += '/';
    }

    std::stringstream listing;
    listing << "<html>"
        << "<head>"
        << "<title>Index of " << directoryPath << "</title>"
        << "<link rel=\"stylesheet\" "
        << "href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css\">"
        << "<style>"
        << "body { font-family: Arial, sans-serif; margin: 0; padding: 0; }"
        << "h1 { font-size: 24px; margin: 20px 0; }"
        << "table { width: 100%; border-collapse: collapse; }"
        << "th, td { padding: 8px; text-align: left; border-bottom: 1px solid #ddd; }"
        << "th { background-color: #f2f2f2; }"
        << "tr:hover { background-color: #f5f5f5; }"
        << "a { text-decoration: none; color: #007bff; display: flex; align-items: center; }"
        << ".icon { margin-right: 10px; font-size: 18px; }"
        << ".folder { color: #FF5733; }"
        << ".file { color: #333; }"
        << "</style>"
        << "</head>"
        << "<body>"
        << "<div class=\"container\">"
        << "<h1>Index of " << directoryPath << "</h1>"
        << "<table>"
        << "<tr><th>Icon</th><th>Name</th><th>Size</th><th>Date Modified</th></tr>";

        std::string dirPath = ROOT + directoryPath;
        dir = opendir(dirPath.c_str());
        while ((ent = readdir(dir)) != NULL) 
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            fullFilePath = dirPath + "/" + ent->d_name;
            if (stat(fullFilePath.c_str(), &filestat) == -1) 
            {
                perror(ent->d_name);
                continue;
            }
            modifiedTime = ctime(&filestat.st_mtime);
            listing << "<tr>";
            listing << "<td>";
            if (S_ISDIR(filestat.st_mode)) 
            {
                listing << "<i class=\"fas fa-folder\"></i>"; // Ícone de pasta
                    ent->d_name[strlen(ent->d_name)] = '/';
            } 
            else 
            {
                listing << "<i class=\"far fa-file\"></i>"; // Ícone de arquivo
            }
            listing << "</td>";
            listing << "<td><a href=\"" << directoryPath << ent->d_name << "\">" << ent->d_name << "</a></td>";
            listing << "<td>" << filestat.st_size << "</td>";
            listing << "<td>" << modifiedTime << "</td>";
            listing << "</tr>";
        }
        closedir(dir);

    listing << "</table>"
            << "</body>"
            << "</html>";

    this->_bodySize = listing.str().length() ;
    char* listingCStr = new char[_bodySize + 1];
    strcpy(listingCStr, listing.str().c_str());
    if (this->_bodySize > 0)
    {
        this->_hasBody = true;
    }
    return listingCStr;
}

char *GetMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    std::string file;

    std::string mockarDirectory =  "on";
    
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else if (mockarDirectory ==  "on")
    {
        return getDirectoryListing();
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
