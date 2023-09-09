#ifndef VALIDATE_BODY_SIZE_LIMIT_H
# define VALIDATE_BODY_SIZE_LIMIT_H

# include <sys/stat.h>
# include <string>

class ValidateBodySizeLimit : public IValidateFunction
{
    public:
        ValidateBodySizeLimit() {}

        virtual bool operator()(std::string &value) const
        {
            return (std::atoi(value.c_str()) > 0);
        }
};

#endif
