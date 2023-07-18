#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h> // For socket functions
# include <netinet/in.h> // For sockaddr_in
# include <cstdlib> // For exit() and EXIT_FAILURE
# include <iostream> // For cout
# include <unistd.h> // For read
# include <cstring> // For strerror
# include <cerrno> // For errno
# include <fstream> // For ifstream
# include <vector> // For vector (duh)

# define PORT 8000
# define BUFFER_SIZE 30000

class Server
{
    public:
        Server();
};

#endif