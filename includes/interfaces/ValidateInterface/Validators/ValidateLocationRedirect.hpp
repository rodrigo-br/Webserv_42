# ifndef VALIDATE_LOCATION_REDIRECT_H
# define VALIDATE_LOCATION_REDIRECT_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include <sys/stat.h>
# include <string>

class ValidateLocationRedirect : public IValidateFunction
{
    public:
        ValidateLocationRedirect() {};

        virtual bool operator()(std::string &path) const
        {
            std::cout <<  " path = "<< path << std::endl;
            struct stat info;
            return (path.find("..") == std::string::npos
                    && path.find("//") == std::string::npos
                    && stat(path.c_str(), &info) == 0
                    && S_ISREG(info.st_mode)
                    && (info.st_mode & S_IRUSR));
        }
};

#endif