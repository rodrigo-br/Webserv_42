#include "classes/Cgi.hpp"

void printEnvArray(char **env) 
{
    for (int i = 0; env[i] != NULL; i++) {
        std::cout << env[i] << std::endl;
    }
}
Cgi::Cgi(Request &request, RequestValidator &validator)
{
	this->initEnv(request, validator);
	char **envArray = createEnvironmentArray();
	printEnvArray(envArray);

}

std::string intToString(int value) 
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}



void		Cgi::initEnv(Request &request, RequestValidator &validator) {

	(void)validator;
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";
	// if (headers.find("Hostname") != headers.end())
		this->_env["SERVER_NAME"] = request.getHeader("Hostname");
	// else
	// 	this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_PORT"] = request.getPort();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["PATH_INFO"] = request.getPath();
	this->_env["PATH_TRANSLATED"] = request.getPath();
	this->_env["SCRIPT_NAME"] = request.getPath();
	this->_env["QUERY_STRING"] = request.getQuery();
	this->_env["REMOTEaddr"] =  "127.0.0.1"; ////////////////// TA MANUAL PRECISA CRIAR FUNCAO
	this->_env["AUTH_TYPE"] = request.getHeader("Authorization");
	this->_env["REMOTE_USER"] = request.getHeader("Authorization");
	this->_env["REMOTE_IDENT"] = request.getHeader("Authorization");
	this->_env["CONTENT_TYPE"] = request.getHeader("Content-Type");
	this->_env["CONTENT_LENGTH"] = intToString(request.getBody().length());
	this->_env["REDIRECT_STATUS"] = "200";
	this->_env["SCRIPT_FILENAME"] = request.getPath();
	this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
}

char **Cgi::createEnvironmentArray() const 
{
    char	**env = new char*[this->_env.size() + 1];
    int		j = 0;

    for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) 
	{
        std::string element = i->first + "=" + i->second;
        
        env[j] = new char[element.size() + 1];
        strcpy(env[j], element.c_str());
        
        j++;
    }
    env[j] = NULL;
    
    return env;
}
