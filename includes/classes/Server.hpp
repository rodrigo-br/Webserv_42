#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 30000


class Server
{
    public:
        static bool gSignalInterrupted;
        Response response;
        Conf conf;
        Server();
        static void signalHandler(int signum);
};

#endif
