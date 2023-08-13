#ifndef VALIDATE_PORT_IS_SAFE_H
# define VALIDATE_PORT_IS_SAFE_H

# include "interfaces/ValidateInterface/IValidateFunction.hpp"

template <size_t N>
class ValidatePortIsSafe : public IValidateFunction
{
    private:
        int _unsafePorts[N];

    public:
        ValidatePortIsSafe(int (&unsafePorts)[N])
        {
            for (size_t i = 0; i < N; ++i)
            {
                _unsafePorts[i] = unsafePorts[i];
            }
        }

        virtual bool operator()(std::string &portInput) const
        {
            int port = std::atoi(portInput.c_str());
            if (_unsafePorts != NULL && (port != 0 || portInput == "0"))
            {
                if (port > 1024 && port < 49151)
                {
                    for (size_t i = 0; i < N; ++i)
                    {
                        if (port == _unsafePorts[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;
        }
};

#endif
