#ifndef METHODS_UTILS_H
# define METHODS_UTILS_H

# include <vector>
# include <iostream>
# include <fstream>
# include <stdlib.h>
# include "enums/StatusCodesEnum.hpp"
# include "classes/StatusCodes.hpp"

class MethodsUtils
{
    public:
        StatusCodesEnum::statusCodes    statusCode;
        StatusCodes                     _statusCodes;

        std::vector<char>   openFileAsVector(std::string path);
        std::string         getExtension(std::string path) const;
        std::string         getProtocolVersion() const;
        std::string         get_status_code() const;
        std::string         get_status_msg() const;
};

#endif
