#ifndef UTILS_HPP
#define UTILS_HPP

# include <string>
# include <iostream>
# include <cstring>
# include <cerrno>
# include <sys/types.h>
# include "enums/HttpMethodsEnum.hpp"

class Utils {

    public:
        static bool check(ssize_t result, std::string functionToBeChecked, int erro = -1);
        static bool hasMethodInInput(std::string input, HttpMethodEnum::httpMethod method);
        static bool endsWith(const std::string &str, const std::string &suffix);
        static std::string intToString(int value);
};


#endif
