#include "classes/Utils.hpp"

bool Utils::check(ssize_t result, std::string functionToBeChecked, int erro)
{
    if (result <= erro)
    {
        std::cout << functionToBeChecked << " : " << std::strerror(errno) << std::endl;
        return true;
    }
    return false;
}

bool Utils::hasMethodInInput(int input, HttpMethodEnum::httpMethod method)
{
    return ((input & method) != 0) && ((input & method) != HttpMethodEnum::UNKNOWN) &&
            input >= 1 && input <= 8;
}
