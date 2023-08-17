#include "classes/Cgi.hpp"
#include <sstream> 



#define CGI_BUFSIZE 3000
void printEnvArray(char **env) 
{
    for (int i = 0; env[i] != NULL; i++) {
        std::cout << env[i] << std::endl;
    }
}
Cgi::Cgi(Request &request, RequestValidator &validator)
{
	this->initEnv(request, validator);
	_envp= createEnvironmentArray();
	// printEnvArray(envArray);
        printEnvArray(_args);

	this->_fileScript = request.getPath();
	this->_body = request.getBody();
	this->_scriptName = request.getPath().substr(request.getPath().find_last_of("/") + 1);
	initScriptArguments(request);
	// exec();request

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
		// this->_env["SERVER_NAME"] = request.getHeader("Hostname");
	// else
	// 	this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_PORT"] = request.getPort();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	// this->_env["PATH_INFO"] = request.getPath();
		this->_env["PATH_INFO"] =  "/cgi-bin/index.py";
	// this->_env["PATH_TRANSLATED"] = request.getPath();
	this->_env["SCRIPT_NAME"] =  "index.py";
	this->_env["QUERY_STRING"] = request.getQuery();
	this->_env["REMOTEaddr"] =  "127.0.0.1"; ////////////////// TA MANUAL PRECISA CRIAR FUNCAO
	// this->_env["AUTH_TYPE"] = request.getHeader("Authorization");
	// this->_env["REMOTE_USER"] = request.getHeader("Authorization");
	// this->_env["REMOTE_IDENT"] = request.getHeader("Authorization");
	// this->_env["CONTENT_TYPE"] = request.getHeader("Content-Type");
	this->_env["CONTENT_LENGTH"] = intToString(request.getBody().length());
	this->_env["REDIRECT_STATUS"] = "200";
	std::string const path = "/cgi-bin/index.py";
	// std::string const scriptName = path.substr(path.find_last_of("/") + 1);
	// this->_env["SCRIPT_FILENAME"] = 
	this->_env["REQUEST_URI"] = path + request.getQuery();
	this->_env["HTTP_ACCEPT"] = request.getHeader("Accept");
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["HTTP_HOST"] = request.getHeader("Host");

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

char      **Cgi::createArrayOfStrings(std::vector<std::string> const &argsVars) const
{
	char **arg = new char *[argsVars.size() + 1];
        std::cout <<  "-------------------------------------- " << std::endl;

	for (std::size_t i = 0; i < argsVars.size(); ++i)
	{
		arg[i] = new char[argsVars[i].size() + 1];
        std::cout <<  "arg[i] " <<  arg[i] << std::endl;
		std::strcpy(arg[i], argsVars[i].c_str());
	}
	arg[argsVars.size()] = NULL;

	return arg;
}

void Cgi::initScriptArguments(Request &request)
{
            std::cout <<  "arg[i] aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"  << _fileScript << std::endl;
            std::cout <<  "arg[i] aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"  << request.getBody() << std::endl;

	std::vector<std::string> argmunts;



	this->_script = "py";

	argmunts.push_back(this->_script);
	argmunts.push_back(this->_fileScript);
	argmunts.push_back(request.getBody());
	this->_args = createArrayOfStrings(argmunts);
}

std::string		Cgi::executeCgi() 
{
    pid_t pid;

    std::string newBody;

    // Create and manage pipes for communication with child process
    int inPipe[2];
    int outPipe[2];


    if (pipe(inPipe) < 0 || pipe(outPipe) < 0)
    {
        return "Status: 500\r\n\r\n";
    }

    // Fork a child process
    pid = fork();

    if (pid == -1)
    {
        return "Status: 500\r\n\r\n";
    }
    else if (pid == 0) // Child process
    {
        close(inPipe[1]);  // Close write end of input pipe
        close(outPipe[0]); // Close read end of output pipe

        // Redirect stdin and stdout to the pipes
        dup2(inPipe[0], STDIN_FILENO);
        dup2(outPipe[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(inPipe[0]);
        close(outPipe[1]);

        // Execute the CGI script
        char *const *nll = NULL;
		std::string  novo = "/usr/bin/" + _script;
        execve(novo.c_str(), nll, _envp);
 	std::cerr << "-----------------------Error executing CGI script-----------------" << std::endl;
        // If execve fails, write an error response
        write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
        exit(1);
    }
    else // Parent process
    {
        close(inPipe[0]);  // Close read end of input pipe
        close(outPipe[1]); // Close write end of output pipe

        // Write the request body to the child process
        write(inPipe[1], _body.c_str(), _body.size());
        close(inPipe[1]);

        // Read the CGI script's output from the pipe
        char buffer[CGI_BUFSIZE];
        ssize_t bytesRead;

        while ((bytesRead = read(outPipe[0], buffer, sizeof(buffer))) > 0)
        {
            newBody.append(buffer, bytesRead);
        }
        close(outPipe[0]);

        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        return newBody;
    }
}
