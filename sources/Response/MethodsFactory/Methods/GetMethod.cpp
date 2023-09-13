#include "interfaces/MethodsFactory/Methods/GetMethod.hpp"
#include <sstream> // Precisa ficar neste arquivo para evitar erro de incomplete type no test (C++11)
#include <dirent.h>

const char* GetMethod::buildResponse()
{
    std::string response;

    response.append(this->build_start_line());
    response.append(this->build_headers());
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

std::string GetMethod::build_headers()
{
    std::string headers;
    headers.append("Content-Type: ");
    headers.append(this->get_content_type());
    headers.append("\r\n\n");
    return headers;
}

void addHeader(std::stringstream& listing, const std::string& directoryPath)
{
    listing << "<html>"
            << "<head>"
            << "<title>Index of " << directoryPath << "</title>"
            << "<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@1/css/pico.min.css\">"
            << "<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css\">"
            << "</head>"
            << "<body>"
            << "<div class=\"container\">"
            << "<h1 class=\"mt-5 mb-4\">Index of " << directoryPath << "</h1>"
            << "<table class=\"table\">"
            << "<thead class=\"table-light\">"
            << "<tr><th>Name</th><th>Size</th><th>Date Modified</th></tr>"
            << "</thead>"
            << "<tbody>";
}

void addItemToTable(std::stringstream& listing, const std::string& itemName, struct stat &filestat, std::string directoryPath, std::string root)
{
    std::string fullFilePath, modifiedTime;

    modifiedTime = ctime(&filestat.st_mtime);
    listing << "<tr>";
    listing << "<td>";
    if (S_ISDIR(filestat.st_mode))
    {
        listing << "<i class=\"fas fa-folder\"></i>  ";
        listing << "<a href=\"" << directoryPath.substr(std::string(root).length()) << itemName + "/" << "\">" << itemName + "/" << "</a>";
    }
    else
    {
        listing << "<i class=\"far fa-file\"></i>  ";
        listing << "<a href=\"" << directoryPath.substr(std::string(root).length()) << itemName << "\">" << itemName << "</a>";
    }
    listing << "</td>";
    listing << "<td>" << filestat.st_size << "</td>";
    listing << "<td>" << modifiedTime << "</td>";
    listing << "</tr>";
}

char *GetMethod::getDirectoryListing()
{
    DIR             *dir;
    struct dirent   *ent;
    struct stat     filestat;
    std::string     fullFilePath;
    std::stringstream listing;
    std::string     directoryPath = this->request.getPath();

    if (!this->request.getHeader("Referer").empty())
    {
        directoryPath = std::string(this->root) + "/" + directoryPath;
    }
    addHeader(listing, directoryPath);
    dir = opendir(directoryPath.c_str());
    if (!dir)
    {
        this->_isDirectoryList   = false;
        std::string file = this->root + std::string("/statusCodes/404.html");
        this->statusCode = StatusCodesEnum::NOT_FOUND;
        char* errorCStr = new char[file.size() + 1];
        strcpy(errorCStr, file.c_str());
        return errorCStr;
    }
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
        fullFilePath = directoryPath + "/" + ent->d_name;
        if (stat(fullFilePath.c_str(), &filestat) == -1)
        {
            perror(ent->d_name);
            continue;
        }
        addItemToTable(listing, ent->d_name, filestat, directoryPath, this->root);
    }
    closedir(dir);
    listing << "</table>"
            << "</body>"
            << "</html>";
    this->_bodySize = listing.str().length() ;
    char* listingCStr = new char[_bodySize + 1];
    strcpy(listingCStr, listing.str().c_str());
    this->_isDirectoryList = true;
    this->statusCode = StatusCodesEnum::OK;
    return listingCStr;
}

char *GetMethod::BODY_BUILDER_BIIIIHHHHLLL()
{
    std::string file;
    char * body;

    if (!this->validator.getMethodAllowed() && (this->validator.getPath() || this->validator.isDirectoryListing()))
    {
        file = this->root + this->validator.getErrorPage(405);
        this->statusCode = StatusCodesEnum::METHOD_NOT_ALLOWED;
    }
    else if (this->validator.getPath())
    {
        file = this->request.getPath();
        this->statusCode = StatusCodesEnum::OK;
    }
    else if (this->validator.isDirectoryListing())
    {
        body = getDirectoryListing();
    }
    else
    {
        file = this->root + this->validator.getErrorPage(404);
        this->statusCode = StatusCodesEnum::NOT_FOUND;
    }
    if (this->_isDirectoryList == false)
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

std::string GetMethod::get_content_type()
{
    std::string file;
    if (this->validator.getPath())
    {
        file = this->request.getPath();
    }
    else
    {
        file = this->root + std::string(this->validator.getErrorPage(404));
    }
    return this->_contentTypes.getMimeType(this->getExtension(file));
}
