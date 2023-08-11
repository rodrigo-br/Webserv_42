#ifndef DELETE_METHOD_H
# define DELETE_METHOD_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <fstream>
# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include "interfaces/IMethod.hpp"

class DeleteMethod : public IMethod
{
    public:
        const char  *buildResponse();
        const char  *buildBody();
        ssize_t     getbodySize() const;
        bool        hasBody() const;
};

#endif
