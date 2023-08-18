#include "classes/Cgi.hpp"\

#define CGI_BUFSIZE 3000
void printEnvArray(char **env) 
{
    for (int i = 0; env[i] != NULL; i++) {
        std::cout << env[i] << std::endl;
    }
}

Cgi::Cgi(Request &request)
{
	this->initEnv(request);
	_envp = createEnvironmentArray();
    _pathTemp =  "wwwroot" + request.getPath();
    std::cout << request.getPath()<< std::endl;
	this->_fileScript = _pathTemp;
	this->_body = request.getBody();
	this->_scriptName = _pathTemp.substr(_pathTemp.find_last_of("/") + 1);
	initScriptArguments(request);

}
Cgi::~Cgi(void)
{
    freeArrayOfStrings(_args);
    freeArrayOfStrings(_envp);
}

void		Cgi::initEnv(Request &request) 
{
	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_PORT"] = request.getPort();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["PATH_INFO"] =  _pathTemp;
    std::string const scriptName =_pathTemp.substr(_pathTemp.find_last_of("/") + 1);
	std::cout << scriptName << std::endl;
	this->_env["SCRIPT_NAME"] =  scriptName;
	this->_env["QUERY_STRING"] = request.getQuery();
	this->_env["CONTENT_LENGTH"] = Utils::intToString(request.getBody().length());
	this->_env["REDIRECT_STATUS"] = "200";
	std::string const path = _pathTemp;
	this->_env["REQUEST_URI"] = path + request.getQuery();
	this->_env["HTTP_ACCEPT"] = request.getHeader("Accept");
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["HTTP_HOST"] = request.getHeader("Host");

}

char **Cgi::createEnvironmentArray() const 
{
    std::string element;
    char	**env = new char*[this->_env.size() + 1];
    int		j = 0;

    for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) 
	{
        element = i->first + "=" + i->second;
        env[j] = new char[element.size() + 1];
        strcpy(env[j], element.c_str());
        j++;
    }
    env[j] = NULL;
    return env;
}

char      **Cgi::createArrayOfStrings(std::vector<std::string> const &argsVars) const
{
	char **arg = new char *[argsVars.size() + 1];

	for (std::size_t i = 0; i < argsVars.size(); ++i)
	{
		arg[i] = new char[argsVars[i].size() + 1];
		std::strcpy(arg[i], argsVars[i].c_str());
	}
	arg[argsVars.size()] = NULL;
	return arg;
}

void Cgi::initScriptArguments(Request &request)
{
	std::vector<std::string> argmunts;
	this->_script = "python3";
	argmunts.push_back(this->_script);
	argmunts.push_back(this->_fileScript);
	argmunts.push_back(request.getBody());
	this->_args = createArrayOfStrings(argmunts);
}

std::string Cgi::executeCgi() 
{
    std::string fullNameScript;
    pid_t       pid;
    int         status;
    int         tempFile;

    tempFile = open("wwwroot/assets/cgi_temp.html", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (tempFile == -1) 
    {
        close(tempFile);
        return "Status: 500\r\n\r\n";
    }
    pid = fork();
    if (pid == -1) 
    {
        close(tempFile);
        return "Status: 500\r\n\r\n";
    }
    else if (pid == 0)
    {
        dup2(tempFile, STDOUT_FILENO);

        fullNameScript = "/usr/bin/" + this->_script;
        execve(fullNameScript.c_str(), _args, _envp);
        close (tempFile);
        std::cerr << "-----------------------Error executing CGI script-----------------" << std::endl;
    }
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
    {
        std::cerr << "-----------------------Error executing CGI-----------------" << std::endl;
    }
    close(tempFile);
    return "Status: 200\r\n\r\n";
}

void Cgi::freeArrayOfStrings(char **arg)
{
    if (arg) 
    {
        for (int i = 0; arg[i] != NULL; ++i) 
        {
            delete[] arg[i];
        }
        delete[] arg;
    }
}