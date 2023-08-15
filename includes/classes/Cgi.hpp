#ifndef CGI_HPP
# define CGI_HPP

# include "classes/RequestValidator.hpp"
# include "classes/Request.hpp"
# include <string>
#include <sstream> 

class Cgi
{
	public:
		Cgi(Request &request, RequestValidator &validator);
	
	private:
		Cgi(void);
		void								initEnv(Request &request, RequestValidator &validator);
		char **								createEnvironmentArray() const;

		std::map<std::string, std::string>	_env;
};


#endif