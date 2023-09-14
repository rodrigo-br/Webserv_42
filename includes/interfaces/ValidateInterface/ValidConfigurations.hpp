#ifndef VALID_CONFIGURATIONS_H
# define VALID_CONFIGURATIONS_H

# include <iostream>
# include <string>
# include <map>
# include <set>
# include <cstdlib>
# include "interfaces/ValidateInterface/IValidateFunction.hpp"
# include "interfaces/ValidateInterface/Validators/ValidatePortIsSafe.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateDirectoryExist.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateMethods.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateLocationIndex.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateLocationRedirect.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateGenericConfiguration.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateServerNames.hpp"
# include "interfaces/ValidateInterface/Validators/ValidateBodySizeLimit.hpp"

class ValidConfigurations
{
    private:
        std::map<std::string, IValidateFunction*> _serverConfigurations;
        std::map<std::string, IValidateFunction*> _locationConfigurations;

    public:
        ValidConfigurations();
        ~ValidConfigurations();
        bool ValidateAServerConfiguration(std::string &key, std::string &value);
        bool ValidateALocationConfiguration(std::string &key, std::string &value);
};

#endif
