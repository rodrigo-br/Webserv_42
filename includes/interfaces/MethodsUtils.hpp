#ifndef METHODS_UTILS_H
# define METHODS_UTILS_H

# include <vector>
# include <iostream>
# include <fstream>
# include <stdlib.h>

class MethodsUtils
{
    public:
        std::vector<char>   open_file_as_vector(std::string path);
        std::string         get_extension(std::string path) const;
        std::string         get_protocol_version() const;
};

#endif
