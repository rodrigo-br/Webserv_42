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
        static bool check(ssize_t result, int erro = -1);
        static bool hasMethodInInput(int input, HttpMethodEnum::httpMethod method);

};

#endif
