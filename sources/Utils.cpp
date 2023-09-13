#include "classes/Utils.hpp"
#include <sstream>

bool Utils::check(ssize_t result, std::string functionToBeChecked, int erro)
{
    if (result <= erro)
    {
        std::cerr << functionToBeChecked << " : " << std::strerror(errno) << std::endl;
        return true;
    }
    return false;
}

bool Utils::checkSend(ssize_t result, std::string functionToBeChecked, int erro)
{
    if (result == erro)
    {
        std::cerr << functionToBeChecked << " : " << std::strerror(errno) << std::endl;
        return true;
    }
    else if (result == 0)
    {
        std::cerr << functionToBeChecked << " : " << std::strerror(errno) << std::endl;
        return true;
    }
    return false;
}

bool Utils::hasMethodInInput(int input, HttpMethodEnum::httpMethod method)
{
    return ((input & method) != 0) && ((input & method) != HttpMethodEnum::UNKNOWN) &&
            input >= 1 && input <= 8;
}

bool Utils::endsWith(const std::string &str, const std::string &suffix)
{
    if (str.length() < suffix.length())
	{
        return false;
    }
    return str.substr(str.length() - suffix.length()) == suffix;
}

std::string Utils::intToString(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int Utils::stringToInt(const std::string& str)
{
    std::stringstream ss(str);
    int value = 0;
    ss >> value;
    return value;
}

bool  Utils::isDelimiter(std::string line, std::string delimiter)
{
	return (line.rfind(delimiter) != std::string::npos);
}


bool Utils::hasQuery(std::string query, std::string name)
{
    return (query.find(name) != std::string::npos);
}

void	 Utils::readLine(int fd, std::string &line, std::string delimiter, bool &error)
{
    char		buffer[2] = {0};
	ssize_t		numberBytes;
	std::string tempLine;

	while (true)
	{
		numberBytes = recv(fd, buffer, 1, 0);
		if (numberBytes == -1)
        {
            error = true;
            std::cerr << "readLine: " << std::strerror(errno) << std::endl;
			break;
        }
		if (numberBytes == 0)
        {
            error = true;
            std::cerr << "readLine: " << std::strerror(errno) << std::endl;
			break ;
        }
		tempLine += buffer;
        if (isDelimiter(tempLine, delimiter))
            break ;
	}
	line = tempLine;
    if (isDelimiter(tempLine, delimiter))
		line.resize(line.rfind(delimiter));
}

void	 Utils::readLineBody(int fd, std::string &line, int contentLength, bool &error)
{
    ssize_t		numberBytes;
    char		buffer[20] = {0};

    while (true)
    {
        if (!contentLength)
            break;
        numberBytes = recv(fd, buffer, 20, 0);
		if (numberBytes == -1)
        {
            error = true;
            std::cerr << "readLineBody: " << std::strerror(errno) << std::endl;
			break;
        }
		if (numberBytes == 0)
        {
            error = true;
            std::cerr << "readLineBody: " << std::strerror(errno) << std::endl;
			break ;
        }
        contentLength -= numberBytes;
        line.append(buffer, numberBytes);
        memset(buffer, 0, 20);
    }
}
