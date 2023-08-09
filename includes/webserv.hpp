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
# include <map> // For map (duh)
# include <csignal> // For signal
# include <sys/select.h> // For select function
# include "classes/Utils.hpp"
# include "classes/ResponseBuilder.hpp"
# include "classes/RequestParser.hpp"
# include "classes/Request.hpp"
# include "classes/RequestValidator.hpp"
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include "classes/Response.hpp"
# include "classes/Conf.hpp"
# include "classes/Server.hpp"
# include "classes/ConfParser.hpp"
# include "enums/HttpMethodsEnum.hpp"
# include "enums/StatusCodesEnum.hpp"

#endif
