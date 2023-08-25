#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 30000

class Server
{
    public:
        static bool gSignalInterrupted;
        Server(Conf &config);
        static void signalHandler(int signum);
        time_t getLastTime();

    private:
        void handleNewClients();
        void acceptNewClient(int sockfd);
        void processClients();
        void processClientRequest(int client_sock, Request &request, RequestValidator &validator);
        void sendClientResponse(int client_sock, int i, Request &request, RequestValidator &validator);
        void closeSockets();
        void runServer(Socket socket);
        void setClientesSockets();
        void checkTimeout();
        void closeConnection(const int &i);
void             updateTime();


        Conf conf;
        std::vector<int> listenSockets;
        std::map<time_t, int> clienstSocks;
        fd_set readSocket;
		fd_set writeSocket;
        time_t              _last_msg_time;
};

#endif
