#include "classes/Cgi.hpp"

#define CGI_BUFSIZE 3000

pid_t Cgi::childPid = 0;

Cgi::Cgi(Request &request, std::string root, std::string name) : _fdExec(0)
{
	this->initEnv(request, name);
	createEnvironmentArray();
    this->_root = root;
    request.setFileExec(root + "/assets/cgi_temp.html");
    this->_fileExec = request.getFileExec();
    this->_pathTemp = _root + request.getPath();
    if (name.length() > 0)
    {
        this->_pathTemp += "cgipost.py";
    }
	this->_fileScript = this->_pathTemp;
	this->_body = request.getBody();
	this->_scriptName = this->_pathTemp.substr(this->_pathTemp.find_last_of("/") + 1);
	initScriptArguments(request);

}

Cgi::~Cgi(void)
{
    if (this->_fdExec)
    {
        close(this->_fdExec);
    }
    freeArrayOfStrings(this->_args);
    freeArrayOfStrings(this->_envp);
}

void		Cgi::initEnv(Request &request, std::string name)
{
	this->_env["SERVER_SOFTWARE"] = "Webserv/1.0";
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_PORT"] = request.getPort();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["PATH_INFO"] =  this->_pathTemp;
    std::string const scriptName = this->_pathTemp.substr(this->_pathTemp.find_last_of("/") + 1);
	std::cout << scriptName << std::endl;
	this->_env["SCRIPT_NAME"] =  scriptName;
	this->_env["QUERY_STRING"] = request.getQuery();
	this->_env["CONTENT_LENGTH"] = Utils::intToString(request.getBody().length());
	this->_env["REDIRECT_STATUS"] = "200";
	std::string const path = this->_pathTemp;
	this->_env["REQUEST_URI"] = path + request.getQuery();
	this->_env["HTTP_ACCEPT"] = request.getHeader("Accept");
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["HTTP_HOST"] = request.getHeader("Host");
    this->_env["NAME"] = name;
}

void    Cgi::createEnvironmentArray()
{
    std::string     element;
    int             j = 0;

    this->_envp = new char*[this->_env.size() + 1];
    for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++)
	{
        element = i->first + "=" + i->second;
       this->_envp[j] = new char[element.size() + 1];
        strcpy(this->_envp[j], element.c_str());
        j++;
    }
    this->_envp[j] = NULL;
}

void    Cgi::createArgumentsArray(std::vector<std::string> const &argsVars)
{
	this->_args = new char *[argsVars.size() + 1];

	for (std::size_t i = 0; i < argsVars.size(); ++i)
	{
		this->_args[i] = new char[argsVars[i].size() + 1];
		std::strcpy(this->_args[i], argsVars[i].c_str());
	}
	this->_args[argsVars.size()] = NULL;
}

void Cgi::initScriptArguments(Request &request)
{
	std::vector<std::string> argmunts;
	this->_script = "python3";
	argmunts.push_back(this->_script);
	argmunts.push_back(this->_fileScript);
	argmunts.push_back(request.getBody());
	createArgumentsArray(argmunts);
}

void timeoutHandler(int sign)
{
    (void)sign;
    kill(Cgi::childPid, SIGTERM);
}

bool Cgi::executeCgi()
{
    std::string fullNameScript;
    pid_t       pid;
    int         status;
    signal(SIGALRM, timeoutHandler);
    alarm(15);

    this->_fdExec = open(_fileExec.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (this->_fdExec == -1)
    {
        return false;
    }
    pid = fork();
    Cgi::childPid = pid;
    if (pid == -1)
    {
        return false;
    }
    else if (pid == 0)
    {
        dup2(this->_fdExec, STDOUT_FILENO);

        fullNameScript = "/usr/bin/" + this->_script;
        execve(fullNameScript.c_str(), this->_args, this->_envp);
        std::cerr << "-----------------------Error executing CGI script-----------------" << std::endl;
    }
    waitpid(pid, &status, 0);
    alarm(0);
    if (WIFSIGNALED(status))
    {
        std::cerr << "TIMEOUT" << std::endl;
        std::cerr << "-----------------------Error executing CGI-----------------" << std::endl;
        return false;
    }
    return true;
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
