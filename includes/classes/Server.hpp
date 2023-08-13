#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 30000

class Server
{
    public:
        static bool gSignalInterrupted;
        Conf conf;
        Server(Conf &config);
        static void signalHandler(int signum);

        void runServer(Socket socket);
        std::vector<int> listenSockets;
        std::vector<int> clienstSocks;
};

#endif
