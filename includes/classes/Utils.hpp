
#ifndef UTILS_HPP
#define UTILS_HPP

# include <string>
# include <sstream>
# include <iostream>
# include <cstring> 
# include <cerrno>
# include <sys/types.h>

class Utils {
    
    public:
        static bool check(ssize_t result, int erro = -1);

};

#endif 