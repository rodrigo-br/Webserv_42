#include "classes/Cgi.hpp"

Cgi::Cgi(Request &request, RequestValidator &validator)
{
	this->initEnv(request, validator);
}

void		Cgi::initEnv(Request &request, RequestValidator &validator) {

	(void)validator;
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";
	// if (headers.find("Hostname") != headers.end())
	// 	this->_env["SERVER_NAME"] = headers["Hostname"];
	// else
	// 	this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_PORT"] = request.getPort();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["PATH_INFO"] = request.getPath();
	this->_env["PATH_TRANSLATED"] = request.getPath();
	this->_env["SCRIPT_NAME"] = request.getPath();
	// this->_env["QUERY_STRING"] = request.getQuery();
	// this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
	// 	this->_env["AUTH_TYPE"] = request.getHeader("Authorization");
	// this->_env["REMOTE_USER"] = request.getHeader("Authorization");
	// this->_env["REMOTE_IDENT"] = request.getHeader("Authorization");
	this->_env["CONTENT_TYPE"] = request.getHeader("Content-Type");
	// this->_env["CONTENT_LENGTH"] = to_string(this->_body.length());
	
	this->_env["REDIRECT_STATUS"] = "200";
	this->_env["SCRIPT_FILENAME"] = request.getPath();
	// this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
}