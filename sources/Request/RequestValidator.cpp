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
	std::string	path = request.get_path();
	size_t		position = path.find_last_of("/");
	size_t		len = path.length();
	std::string root = conf.get_root();

	if (len == 1 && (path.compare("/") == 0))//verifica "/"
	{
		std::string location = conf.get_locations(path);
		if (!location.empty())
		{
			this->_path = true;
			request.set_path(root + path + location);
		}
	}
	else if (len == position + 1)//verifica se a / está na última posição
	{
		std::string location = conf.get_locations(path.substr(0, len - 1));
		if (!location.empty())
		{
			this->_path = true;
			request.set_path(root + path + location);
		}
	}
	else//não termina com /
	{
		std::string test = conf.get_locations(path);
		if (!test.empty())//verifica se não está dando o caminho SEM o arquivo (exemplo http://localhost:8000/api/upload)
		{
			this->_path = true;
			request.set_path(root + path + "/" + test);
			return ;
		}
		std::string location = conf.get_locations(path.substr(0, position));
		if (!location.empty())// para casos em que tem um caminho válido com algum arquivo ainda não verificado
		{
			if (location.compare(path.substr(position + 1)) == 0)// verifica se o arquivo está ok
			{
				this->_path = true;
				request.set_path(root + path);
			}
		}
		else//tudo deu errado
		{
			if (path.compare("/index.html") == 0)// é simplesmente /index.html?
			{
				this->_path = true;
				request.set_path(root + path);
			}
		}

	}
	if (path.find("/assets") != std::string::npos)//verifica se é assets mas sem verificar se existe referer
	{
		if (!request.get_header("Referer").empty())// verifica se é referer
		{
			this->_path = true;
			request.set_path(root + path);
		}
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
