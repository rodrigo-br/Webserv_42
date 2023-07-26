#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define PORT 8000
# define BUFFER_SIZE 30000


class Server
{
    public:
        static bool gSignalInterrupted;
        Response response;
        Server();
        static void signalHandler(int signum);
};

#endif
