#ifndef getMethod_H
# define getMethod_H

# include <string>
# include "classes/ContentTypes.hpp"
# include "classes/StatusCodes.hpp"
# include <fstream>
# include <iostream>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include "interfaces/MethodsFactory/IMethod.hpp"

class GetMethod : public IMethod
{
    public:
        const char  *buildResponse();
        const char  *buildBody();
        ssize_t     getbodySize() const;
        bool        hasBody() const;

    private:
        ContentTypes _contentTypes;
        bool        _hasBody;
        ssize_t     _bodySize;
        bool        _isDirectoryList;

        std::string build_start_line() const;
        std::string build_headers();
        char *BODY_BUILDER_BIIIIHHHHLLL();
        std::string get_content_type();
        char        *getDirectoryListing() ;
};

#endif
