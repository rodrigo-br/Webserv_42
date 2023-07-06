#include "Server.hpp"

// static int create_socket(sockaddr_in &sockaddr)
// {
// 	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (sockfd == -1)
// 	{
// 		std::cout << "Failed to create socket. errno: " << errno << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	sockaddr.sin_family = AF_INET;
// 	sockaddr.sin_addr.s_addr = INADDR_ANY;
// 	sockaddr.sin_port = htons(PORT);
// 	return sockfd;
// }

// static void bind_socket(int &sockfd, sockaddr_in &sockaddr)
// {
// 	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
// 		std::cout << "Failed to bind to port " << PORT << ". errno: " << errno << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// }

// static void listen_socket(int &sockfd)
// {
// 	if (listen(sockfd, 10) < 0) {
// 		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// }

// static int accept_socket(int &sockfd, sockaddr_in &sockaddr, int &addrlen)
// {
// 	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
// 	if (connection < 0) {
// 		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	return connection;
// }

// static void read_from_connection(int &connection, char *buffer)
// {
// 	int bytesRead = read(connection, buffer, BUFFER_SIZE);
// 	if (bytesRead <= 0)
// 	{
// 		std::cout << "No msg read" << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	std::cout << "The message was: " << buffer;
// }

int Server::getPort() { return PORT; };

Server::Server()
{
	// sockaddr_in sockaddr;
	// int sockfd = create_socket(sockaddr);
	// bind_socket(sockfd, sockaddr);
	// listen_socket(sockfd);
	// int addrlen = sizeof(sockaddr);

	// while(1)
	// {
	// 	int connection = accept_socket(sockfd, sockaddr, addrlen);

	// 	char buffer[BUFFER_SIZE] = {0};
	// 	read_from_connection(connection, buffer);
	// 	std::ifstream file("Dogs.png", std::ios::binary | std::ios::ate);

	// 	if (!file.is_open())
	// 	{
	// 		std::cout << "Failed to open image file." << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	std::streamsize size = file.tellg();
	// 	file.seekg(0, std::ios::beg);
	// 	std::vector<char> imageBuffer(size);
	// 	if (!file.read(imageBuffer.data(), size))
	// 	{
	// 		std::cout << "Failed to read image file" << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	file.close();

	// 	std::string response = "HTTP/1.1 200 OK\nContent-Type: image/png\n\n";
	// 	send(connection, response.c_str(), response.size(), 0);
	// 	send(connection, imageBuffer.data(), imageBuffer.size(), 0);

	// 	close(connection);
	// }
	// close(sockfd);
}
