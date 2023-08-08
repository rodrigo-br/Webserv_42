#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 30000


class Server
{
    public:
        static bool gSignalInterrupted;
        Conf conf;
        Server();
        static void signalHandler(int signum);

        void run();
        std::vector<int> listen_sockets;
        fd_set current_sockets;
        int max_socket_so_far;
};

#endif
