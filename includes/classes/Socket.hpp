#ifndef SOCKET_HPP
# define SOCKET_HPP


# include  "classes/ServerData.hpp"
# include  "classes/Utils.hpp"
# include <vector>
# include <fcntl.h>// For fcntl function
# include <sys/socket.h> // For socket functions
# include <netinet/in.h> // For sockaddr_in
# include <cstdlib> // For exit() and EXIT_FAILURE
# include <unistd.h> // For read

class Socket
{
    public:

        Socket(std::map<int, ServerData>& conf );
        std::vector<int> getlistenSockets();
        fd_set getReadFds();
        fd_set getWriteFds();
        bool succeed();


    private:

        bool initializeSockets(std::map<int, ServerData>& conf);
        std::vector<int> _listenSockets;
        fd_set _readFds;
        fd_set _writeFds;
        bool _succeed;



};

#endif