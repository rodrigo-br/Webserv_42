#ifndef VALIDATE_LOCATION_INDEX_H
# define VALIDATE_LOCATION_INDEX_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include <sys/stat.h>
# include <string>

class ValidateLocationIndex : public IValidateFunction
{
    public:
        ValidateLocationIndex() {};

        virtual bool operator()(std::string &path) const
        {
            struct stat info;
            return (path.find("..") == std::string::npos
                    && path.find("//") == std::string::npos
                    && stat(path.c_str(), &info) == 0
                    && S_ISREG(info.st_mode)
                    && (info.st_mode & S_IRUSR));
        }
};

#endif
