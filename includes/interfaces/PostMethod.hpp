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
# include "interfaces/IMethod.hpp"

class PostMethod : public IMethod
{
    public:
        const char  *build_response();
        const char  *build_body();
        ssize_t     get_body_size() const;
        bool        has_body() const;
};

#endif
