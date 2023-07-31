#include "classes/Utils.hpp"

bool Utils::check(ssize_t result, int erro) 
{
    if (result <= erro) 
    {
        std::cout << std::strerror(errno) << std::endl;
        return true;
    }
    return false;
}