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
# include "interfaces/MethodsFactory/IMethod.hpp"

class DeleteMethod : public IMethod
{
    public:
        const char      *buildResponse();
        const char      *buildBody();
        ssize_t         getbodySize() const;
        bool            hasBody() const;
        
    private:
        ContentTypes    _contentTypes;
        StatusCodes     _statusCodes;
        bool            _hasBody;
        ssize_t         _bodySize;
        
        std::string     build_start_line() const;
        std::string     build_headers() const;
        char            *BODY_BUILDER_BIIIIHHHHLLL();
        std::string     get_status_code() const;
        std::string     get_status_msg() const;
        std::string     get_content_type() const;
};

#endif
