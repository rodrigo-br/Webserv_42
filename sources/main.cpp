#include "webserv.hpp"

int main(int argc, char *argv[])
{
    if (argc < 1 || argc > 2)
    {
        std::cout << "Erro nos argumentos informados. Enviar apenas 1 arquivo conf." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string confPath = (argc == 2) ? argv[1] : "./conf/default.conf";
    ConfParser confParser(confPath);
    Server server;

    return 0;
}
