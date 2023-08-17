#ifndef VALIDATE_DIRECTORY_EXIST_H
# define VALIDATE_DIRECTORY_EXIST_H

# include <sys/stat.h>
# include <string>

class ValidateDirectoryExist : public IValidateFunction
{
    public:
        ValidateDirectoryExist() {}

        virtual bool operator()(std::string &path) const
        {
            struct stat info;
            return (path.compare("/") == 0
                    || (path.find("..") == std::string::npos
                    && path.find("//") == std::string::npos
                    && stat(path.c_str(), &info) == 0
                    && S_ISDIR(info.st_mode)));
        }
};

#endif
