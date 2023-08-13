#ifndef POST_METHOD_H
# define POST_METHOD_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <fstream>
# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include "interfaces/MethodsFactory/IMethod.hpp"

class PostMethod : public IMethod
{
    public:
        const char  *buildResponse();
        const char  *buildBody();
        ssize_t     getbodySize() const;
        bool        hasBody() const;
};

#endif
