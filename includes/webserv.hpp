#ifndef WEBSERV_H
# define WEBSERV_H

# include <sys/socket.h> // For socket functions
# include <netinet/in.h> // For sockaddr_in
# include <cstdlib> // For exit() and EXIT_FAILURE
# include <iostream> // For cout
# include <unistd.h> // For read
# include <cstring> // For strerror
# include <cerrno> // For errno
# include <fstream> // For ifstream
# include <vector> // For vector (duh)
# include "Response.hpp"
# include "Server.hpp"
# include "HttpMethodsEnum.hpp"
# include "StatusCodesEnum.hpp"

#endif
