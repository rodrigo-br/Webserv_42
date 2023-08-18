#include "classes/RequestValidator.hpp"

RequestValidator::RequestValidator(void) : _method(HttpMethodEnum::UNKNOWN), _path(false), _httpVersion(false), _requestBody(false)  { }

RequestValidator::~RequestValidator(void) {}

RequestValidator &RequestValidator::requestValidator(ServerData &serverData, Request& request)
{
	methodValidator(request);
	pathValidator(serverData, request);
	bodyValidator(request);
	httpVersionValidator(request);
	return *this;
}

HttpMethodEnum::httpMethod RequestValidator::methodValidator(Request& request)
{
	std::string method = request.getMethod();
	if (method.compare("GET") == 0)
		this->_method = HttpMethodEnum::GET;
	else if (method.compare("POST") == 0)
		this->_method = HttpMethodEnum::POST;
	else if (method.compare("DELETE") == 0)
		this->_method = HttpMethodEnum::DELETE;
	return this->_method;
}

void RequestValidator::pathValidator(ServerData &serverData, Request& request)
{
    std::string path = request.getPath();
    std::string root = serverData.getRoot();
	size_t		position = path.find_last_of("/");
	size_t		len = path.length();


    if (isRootPath(path, len))
	{
        handleRootPath(serverData, request, path, root);
	}
    else if (endsWithSlash(position, len))
	{
        handlePathWithTrailingSlash(serverData, request, path, root);
	}
    else
	{
        handleNonTrailingSlashPath(serverData, request, path, root, position);
	}
    handleAssetsPath(request, path, root);
}

bool RequestValidator::isRootPath(const std::string& path, size_t len)
{
    return (len == 1 && (path.compare("/") == 0));
}

bool RequestValidator::endsWithSlash(size_t position, size_t len)
{
    return (len == position + 1);
}

void RequestValidator::handleRootPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root)
{
    std::string location = serverData.getLocation(path);
	// std::cerr << "#------" << location  << "-------#" << std::endl;
	// std::cerr << "#--aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa---#" << std::endl;

    if (!location.empty())
    {
        this->_path = true;
        request.setPath(root + path + location);
    }
}

void RequestValidator::handlePathWithTrailingSlash(ServerData &serverData, Request& request, const std::string& path, const std::string& root)
{
    std::string location = serverData.getLocation(path.substr(0, path.length() - 1));
    if (!location.empty())
    {
        this->_path = true;
        request.setPath(root + path + location);
    }
}

void RequestValidator::handleNonTrailingSlashPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root, size_t position)
{
	std::string location = serverData.getLocation(path);
	if (!location.empty())//verifica se não está dando o caminho SEM o arquivo (exemplo http://localhost:8000/api/upload)
	{
		this->_path = true;
		request.setPath(root + path + "/" + location);
		return ;
	}
	location = serverData.getLocation(path.substr(0, position));
	if (!location.empty())// para casos em que tem um caminho válido com algum arquivo ainda não verificado
	{
		if (location.compare(path.substr(position + 1)) == 0)// verifica se o arquivo está ok
		{

			this->_path = true;
			request.setPath(root + path);
		}
	}
	else
	{
		if (path.compare("/index.html") == 0)// é simplesmente /index.html?
		{
			this->_path = true;
			request.setPath(root + path);
		}
	}

}

void RequestValidator::handleAssetsPath(Request& request, const std::string& path, const std::string& root)
{
    if (path.find("/assets") != std::string::npos && !request.getHeader("Referer").empty())
    {
        this->_path = true;
        request.setPath(root + path);
    }
}

void RequestValidator::bodyValidator(Request& request)
{
	if (!request.getBody().empty())
		this->_requestBody = true;
}

void RequestValidator::httpVersionValidator(Request& request)
{
	if (request.getHttpVersion().compare("HTTP/1.1") == 0)
		this->_httpVersion = true;
}

bool RequestValidator::getPath(void) const
{
	return this->_path;
}

bool RequestValidator::getHttpVersion(void) const
{
	return this->_httpVersion;
}

bool RequestValidator::getBody(void) const
{
	return this->_requestBody;
}

HttpMethodEnum::httpMethod RequestValidator::getMethod(void) const
{
	return this->_method;
}
