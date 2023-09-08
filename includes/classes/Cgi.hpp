#ifndef CGI_HPP
# define CGI_HPP

# include "classes/RequestValidator.hpp"
# include "classes/Request.hpp"
# include "classes/Utils.hpp"
# include <string>
# include <sys/wait.h>
# include <sys/socket.h>
# include <unistd.h>
# include "classes/Utils.hpp"
# include <fcntl.h>
# include <cstdio>

class Cgi
{
	public:
		Cgi(Request &request, std::string root, std::string name="");
		std::string executeCgi() ;
		~Cgi();

	private:
		void		initEnv(Request &request, std::string name);
		void		createEnvironmentArray() ;
		void		initScriptArguments(Request &request);
		void	    createArgumentsArray(std::vector<std::string> const &argsVars);
		void 		freeArrayOfStrings(char **arg);
		std::string	exec(int &socket);

		std::map<std::string, std::string>	_env;
		std::string 						_fileScript;
		std::string							_scriptName;
		std::string							_script;
		std::string							_body;
		std::string							_fileName;
		std::string							_pathTemp;
		std::string							_root;
		std::string							_fileExec;
		char								**_args;
		char								**_envp;
		int									_fdExec;
};


#endif
