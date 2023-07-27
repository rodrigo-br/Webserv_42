#ifndef CONTENT_TYPES_HPP
# define CONTENT_TYPES_HPP

# include <map>
# include <string>

class ContentTypes
{
    private:
        std::map<std::string, std::string> contentTypes;

    public:
        ContentTypes();
        std::string get_mime_type(std::string extension) const;
};

#endif
