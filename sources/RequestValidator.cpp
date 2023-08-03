#include "classes/RequestValidator.hpp"

RequestValidator::RequestValidator(void) : _path(false), _http_version(false), _requestBody(false)  { }

RequestValidator::~RequestValidator(void) {}


static bool path_validator(Conf& conf, Request& request)
{
	std::string	path = request.get_path();
	size_t		position = path.find_last_of("/");
	if (position == path.length() - 1)
	{
		if (!conf.get_locations(path).empty())
			return true;
	}
	else
	{ 
		std::string location = conf.get_locations(path.substr(0, position + 1));
		if (!location.empty())
			if (location.compare(path.substr(position + 1)) == 0)
				return true;
	}
	return false;
}


RequestValidator &RequestValidator::request_validator(Conf& conf, Request& request)
{
	this->_path = path_validator(conf, request);
	if (!request.get_body().empty())
		this->_requestBody = true;
	if (request.get_http_version().compare("HTTP/1.1") == 0)
		this->_http_version = true;
	return *this;
}




bool RequestValidator::get_path(void) const
{
	return _path;
}

bool RequestValidator::get_http_version(void) const
{
	return _http_version;
}

bool RequestValidator::get_body(void) const
{
	return _requestBody;
}
