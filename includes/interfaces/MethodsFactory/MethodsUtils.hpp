#ifndef METHODS_UTILS_H
# define METHODS_UTILS_H

# include <vector>
# include <iostream>
# include <fstream>
# include <stdlib.h>

class MethodsUtils
{
    public:
        std::vector<char>   openFileAsVector(std::string path);
        std::string         getExtension(std::string path) const;
        std::string         getProtocolVersion() const;
};

#endif
