#ifndef STATUS_CODES_HPP
# define STATUS_CODES_HPP

# include <map>
# include <string>
# include "enums/StatusCodesEnum.hpp"

class StatusCodes
{
    private:
        std::map<std::string, std::string> statusCodes;

    public:
        StatusCodes();
        std::string get_status_message(std::string code) const;
};

#endif
