#include "classes/RequestValidator.hpp"

RequestValidator::RequestValidator(void) : _method(HttpMethodEnum::UNKNOWN), _path(false), _http_version(false), _requestBody(false)  { }

RequestValidator::~RequestValidator(void) {}

RequestValidator &RequestValidator::request_validator(Conf& conf, Request& request)
{
	method_validator(request);
	path_validator(conf, request);
	body_validator(request);
	http_version_validator(request);
	return *this;
}

HttpMethodEnum::httpMethod RequestValidator::method_validator(Request& request)
{
	std::string method = request.get_method();
	if (method.compare("GET") == 0)
		this->_method = HttpMethodEnum::GET;
	else if (method.compare("POST") == 0)
		this->_method = HttpMethodEnum::POST;
	else if (method.compare("DELETE") == 0)
		this->_method = HttpMethodEnum::DELETE;
	return this->_method;
}

void RequestValidator::path_validator(Conf& conf, Request& request)
{
    std::string path = request.get_path();
    std::string root = conf.get_root();
	size_t		position = path.find_last_of("/");
	size_t		len = path.length();


    if (isRootPath(path, len))
        handleRootPath(conf, request, path, root);
    else if (endsWithSlash(position, len))
        handlePathWithTrailingSlash(conf, request, path, root);
    else
        handleNonTrailingSlashPath(conf, request, path, root, position);
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

void RequestValidator::handleRootPath(Conf& conf, Request& request, const std::string& path, const std::string& root)
{
    std::string location = conf.get_locations(path);
    if (!location.empty())
    {
        this->_path = true;
        request.set_path(root + path + location);
    }
}

void RequestValidator::handlePathWithTrailingSlash(Conf& conf, Request& request, const std::string& path, const std::string& root)
{
    std::string location = conf.get_locations(path.substr(0, path.length() - 1));
    if (!location.empty())
    {
        this->_path = true;
        request.set_path(root + path + location);
    }
}

void RequestValidator::handleNonTrailingSlashPath(Conf& conf, Request& request, const std::string& path, const std::string& root, size_t position)
{
	std::string location = conf.get_locations(path);
	if (!location.empty())//verifica se não está dando o caminho SEM o arquivo (exemplo http://localhost:8000/api/upload)
	{
		this->_path = true;
		request.set_path(root + path + "/" + location);
		return ;
	}
	location = conf.get_locations(path.substr(0, position));
	if (!location.empty())// para casos em que tem um caminho válido com algum arquivo ainda não verificado
	{
		if (location.compare(path.substr(position + 1)) == 0)// verifica se o arquivo está ok
		{
			this->_path = true;
			request.set_path(root + path);
		}
	}
	else
	{
		if (path.compare("/index.html") == 0)// é simplesmente /index.html?
		{
			this->_path = true;
			request.set_path(root + path);
		}
	}

}

void RequestValidator::handleAssetsPath(Request& request, const std::string& path, const std::string& root)
{
    if (path.find("/assets") != std::string::npos && !request.get_header("Referer").empty())
    {
        this->_path = true;
        request.set_path(root + path);
    }
}

void RequestValidator::body_validator(Request& request)
{
	if (!request.get_body().empty())
		this->_requestBody = true;
}

void RequestValidator::http_version_validator(Request& request)
{
	if (request.get_http_version().compare("HTTP/1.1") == 0)
		this->_http_version = true;
}

bool RequestValidator::get_path(void) const
{
	return this->_path;
}

bool RequestValidator::get_http_version(void) const
{
	return this->_http_version;
}

bool RequestValidator::get_body(void) const
{
	return this->_requestBody;
}

HttpMethodEnum::httpMethod RequestValidator::get_method(void) const
{
	return this->_method;
}
