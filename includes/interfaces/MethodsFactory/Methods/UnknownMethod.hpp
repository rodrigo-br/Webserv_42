#ifndef UNKNOWN_METHOD_H
# define UNKNOWN_METHOD_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <fstream>
# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include "interfaces/MethodsFactory/IMethod.hpp"

class UnknownMethod : public IMethod
{
    public:
        const char  *buildResponse();
        const char  *buildBody();
        ssize_t     getbodySize() const;
        bool        hasBody() const;

    private:
        ContentTypes _contentTypes;
        ssize_t     _bodySize;
        std::string build_start_line() const;
        std::string build_headers();
        std::string get_content_type();
};

#endif
