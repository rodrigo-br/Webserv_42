#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
#include  "classes/Socket.hpp"

# define BUFFER_SIZE 30000

class Server
{
    public:
        static bool gSignalInterrupted;
        Conf conf;
        Server(Conf &config);
        static void signalHandler(int signum);

        bool initializeSockets();
        void runServer(Socket socket);
        void setClients();
        std::vector<int> listenSockets;
        std::vector<int> clienstSocks;
        fd_set read_fds;
        fd_set write_fds;

};

#endif
