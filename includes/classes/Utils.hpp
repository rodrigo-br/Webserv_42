#ifndef UTILS_HPP
#define UTILS_HPP

# include <string>
# include <iostream>
# include <cstring>
# include <cerrno>
# include <sys/types.h>
# include "enums/HttpMethodsEnum.hpp"
# include <sys/socket.h>

class Utils {

    public:
        static bool check(ssize_t result, std::string functionToBeChecked, int erro = -1);
        static bool hasMethodInInput(int input, HttpMethodEnum::httpMethod method);
        static bool endsWith(const std::string &str, const std::string &suffix);
        static std::string intToString(int value);
        static void	readLineBody(int fd, std::string &line, int contentLength);
        static void	readLine(int fd, std::string &line, std::string delimiter);
        static bool isDelimiter(std::string line, std::string delimiter);
        static int stringToInt(const std::string& str);


};


#endif
