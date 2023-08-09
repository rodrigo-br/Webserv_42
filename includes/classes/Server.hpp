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

        void run();
        std::vector<int> listen_sockets;
        fd_set read_fds;
        fd_set write_fds;
        RequestValidator request_validator;
	    Request request ;
        // int client_sock;
         std::vector<int> client_socks;


        int max_socket_so_far;
};

#endif
