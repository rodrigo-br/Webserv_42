#ifndef CGI_HPP
# define CGI_HPP

# include "classes/RequestValidator.hpp"
# include "classes/Request.hpp"
# include "classes/Utils.hpp"
# include <string>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

class Cgi
{
	public:
		Cgi(Request &request);
	std::string executeCgi() ;

	private:
		Cgi(void);
		void								initEnv(Request &request);
		char **								createEnvironmentArray() const;
		void initScriptArguments(Request &request);
		char **     createArrayOfStrings(std::vector<std::string> const &argsVars) const;

		std::string exec(int &socket);
		std::map<std::string, std::string>	_env;
		
		std::string _fileScript;
				std::string _scriptName;

		std::string _script;
		char **_args;
		char **_envp;
		int    fd;
		std::string _body;
		std::string _fileName;
		std::string _pathTemp;
		int _socket;

		
};


#endif