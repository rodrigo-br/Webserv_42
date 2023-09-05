#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE2 30000

class Server
{
    public:
        static bool gSignalInterrupted;
        Server(Conf &config);
        static void signalHandler(int signum);

    private:
        void handleNewClients();
        void acceptNewClient(int sockfd);
        void processClients();
        void processClientRequest(int client_sock, Request &request, RequestValidator &validator);
        void sendClientResponse(int client_sock, int i, Request &request, RequestValidator &validator);
        void closeSockets();
        void runServer(Socket socket);
        void setClientesSockets();

        Conf conf;
        std::vector<int> listenSockets;
        std::vector<int> clienstSocks;
        fd_set readSocket;
		fd_set writeSocket;
};

#endif
