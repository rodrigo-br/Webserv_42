#include "classes/Utils.hpp"
#include <sstream>

bool Utils::check(ssize_t result, std::string functionToBeChecked, int erro)
{
    if (result <= erro)
    {
        std::cout << functionToBeChecked << " : " << std::strerror(errno) << std::endl;
        return true;
    }
    return false;
}

bool Utils::hasMethodInInput(std::string _input, HttpMethodEnum::httpMethod method)
{
    int input;
    if (_input == "GET") { input = 1; }
    else if (_input == "POST") { input = 2; }
    else if (_input == "DELETE") { input = 4; }
    else { input = 0; }
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
