#include "classes/RequestValidator.hpp"

RequestValidator::RequestValidator(void) : _method(HttpMethodEnum::UNKNOWN), _path(false), _httpVersion(false), _requestBody(false), _serverName(false), _isDirectoryListing(false)  { }

RequestValidator::~RequestValidator(void) {}

RequestValidator &RequestValidator::requestValidator(ServerData &serverData, Request& request)
{
	methodValidator(request);
	pathValidator(serverData, request);
	bodyValidator(request);
	httpVersionValidator(request);
	serverNamesValidator(serverData, request);
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
    this->root = serverData.getRoot();
	size_t		position = path.find_last_of("/");
	size_t		len = path.length();

	std::cout << "serverData = " << serverData.getRoot() << std::endl;

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
    handleAssetsPath(request, path, root, serverData);
	handleDirectoryListing(request, path, root, serverData);
}

bool RequestValidator::isRootPath(const std::string& path, size_t len)
{
    return (len == 1 && (path.compare("/") == 0));
}

bool RequestValidator::endsWithSlash(size_t position, size_t len)
{
    return (len == position + 1);
}

void RequestValidator::handleRootPath(ServerData &serverData, Request& request, const std::string& path, const std::string& _root)
{
    std::string location = serverData.getLocation(path);
    if (!location.empty())
    {
        this->_path = true;
		std::cout << "GetAllowed(PATH): " << serverData.getAllowed(path) << " method: " << this->_method << std::endl;
		this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(path));
        request.setPath(_root + path + location);
    }
}

bool	RequestValidator::getMethodAllowed(void) const
{
	return this->_methodAllowed;
}

void RequestValidator::handlePathWithTrailingSlash(ServerData &serverData, Request& request, const std::string& path, const std::string& _root)
{
	std::string correctPath = path.substr(0, path.length() - 1);
    std::string location = serverData.getLocation(correctPath);
    if (!location.empty())
    {
        this->_path = true;
		this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(correctPath));
        request.setPath(_root + path + location);
    }
	else if (serverData.isDirectoryListingLocation(correctPath))
	{
		this->_isDirectoryListing = true;
		request.setPath(_root + path);
	}
}

void RequestValidator::handleNonTrailingSlashPath(ServerData &serverData, Request& request, const std::string& path, const std::string& _root, size_t position)
{

	std::string location = serverData.getLocation(path);
	if (!location.empty())
	{
		this->_path = true;
		this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(path));
		request.setPath(_root + path + "/" + location);
		return ;
	}
	location = serverData.getLocation(path.substr(0, position));
	if (!location.empty())
	{
		if (location.compare(path.substr(position + 1)) == 0)
		{
			this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(path.substr(0, position)));
			this->_path = true;
			request.setPath(_root + path);
		}
	}
	else
	{
		if (path.compare("/index.html") == 0)
		{
			this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed("/"));
			this->_path = true;
			request.setPath(_root + path);
		}
	}

}

void RequestValidator::handleDirectoryListing(Request& request, std::string& path, const std::string& _root, ServerData &serverData)
{
	if (!this->_path && !this->_isDirectoryListing && serverData.isDirectoryListingLocation(path))
	{
		this->_isDirectoryListing = true;
		request.setAllowed(serverData.getAllowed(path));
		request.setPath(_root + path + "/");
		this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(path));
	}
	else if (!this->_path && !request.getHeader("Referer").empty())
	{
		request.setPath(path.substr(1));
		if (path[path.length() - 1] == '/')
		{
			this->_isDirectoryListing = true;
		}
		else
		{
			request.setPath(_root + path);
			this->_path = true;
		}
		this->_methodAllowed = Utils::hasMethodInInput(this->_method, (HttpMethodEnum::httpMethod)serverData.getAllowed(path));
	}
}

bool RequestValidator::isDirectoryListing()
{
	return this->_isDirectoryListing;
}

std::string RequestValidator::getRoot(void) const
{
    return this->root;
}

void RequestValidator::handleAssetsPath(Request& request, const std::string& path, const std::string& _root, ServerData &serverData)
{
    if (path.find("/assets") != std::string::npos && !request.getHeader("Referer").empty())
    {
        this->_path = true;
        request.setPath(_root + path);
		this->_methodAllowed = true;
    }
	else if (path.find("/assets/cgi_temp.html") != std::string::npos)
	{
		this->_path = true;
		request.setPath(_root + path);
		this->_methodAllowed = Utils::hasMethodInInput(HttpMethodEnum::POST, (HttpMethodEnum::httpMethod)serverData.getAllowed("/cgi-bin"));
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

void RequestValidator::setBody(bool body)
{
	this->_requestBody = body;
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

bool RequestValidator::getServerName(void) const
{
	return this->_serverName;
}

HttpMethodEnum::httpMethod RequestValidator::getMethod(void) const
{
	return this->_method;
}

void	RequestValidator::serverNamesValidator(ServerData &serverData, Request& request)
{
	std::vector<std::string> serverNames = serverData.getServerNames();
	for (std::vector<std::string>::const_iterator it = serverNames.begin(); it != serverNames.end(); ++it)
	{
		if ((*it).compare(request.getServerName()) == 0)
		{
			if (request.getPath().find("/assets") != std::string::npos && !request.getHeader("Referer").empty())
			{
				this->_path = true;
			}
			if (request.getPath().find("/assets/cgi_temp.html") != std::string::npos)
			{
				this->_path = true;
			}
			return ;
		}
	}
	this->_path = false;
	this->_isDirectoryListing = false;
}
