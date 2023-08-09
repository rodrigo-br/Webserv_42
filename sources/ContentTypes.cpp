#include "classes/ContentTypes.hpp"

ContentTypes::ContentTypes()
{
    this->contentTypes[".aac"] = "audio/aac";
    this->contentTypes[".abw"] = "application/x-abiword";
    this->contentTypes[".arc"] = "application/x-freearc";
    this->contentTypes[".avif"] = "image/avif";
    this->contentTypes[".avi"] = "video/x-msvideo";
    this->contentTypes[".azw"] = "application/vnd.amazon.ebook";
    this->contentTypes[".bin"] = "application/octet-stream";
    this->contentTypes[".bmp"] = "image/bmp";
    this->contentTypes[".bz"] = "application/x-bzip";
    this->contentTypes[".bz2"] = "application/x-bzip2";
    this->contentTypes[".cda"] = "application/x-cdf";
    this->contentTypes[".csh"] = "application/x-csh";
    this->contentTypes[".css"] = "text/css";
    this->contentTypes[".csv"] = "text/csv";
    this->contentTypes[".doc"] = "application/msword";
    this->contentTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    this->contentTypes[".eot"] = "application/vnd.ms-fontobject";
    this->contentTypes[".epub"] = "application/epub+zip";
    this->contentTypes[".gz"] = "application/gzip";
    this->contentTypes[".gif"] = "image/gif";
    this->contentTypes[".htm"] = "text/html";
    this->contentTypes[".html"] = "text/html";
    this->contentTypes[".ico"] = "image/vnd.microsoft.icon";
    this->contentTypes[".ics"] = "text/calendar";
    this->contentTypes[".jar"] = "application/java-archive";
    this->contentTypes[".jpeg"] = "image/jpeg";
    this->contentTypes[".jpg"] = "image/jpeg";
    this->contentTypes[".js"] = "text/javascript";
    this->contentTypes[".json"] = "application/json";
    this->contentTypes[".jsonld"] = "application/ld+json";
    this->contentTypes[".mid"] = "audio/midi";
    this->contentTypes[".midi"] = "audio/midi";
    this->contentTypes[".mjs"] = "text/javascript";
    this->contentTypes[".mp3"] = "audio/mpeg";
    this->contentTypes[".mp4"] = "video/mp4";
    this->contentTypes[".mpeg"] = "video/mpeg";
    this->contentTypes[".mpkg"] = "application/vnd.apple.installer+xml";
    this->contentTypes[".odp"] = "application/vnd.oasis.opendocument.presentation";
    this->contentTypes[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    this->contentTypes[".odt"] = "application/vnd.oasis.opendocument.text";
    this->contentTypes[".oga"] = "audio/ogg";
    this->contentTypes[".ogv"] = "video/ogg";
    this->contentTypes[".ogx"] = "application/ogg";
    this->contentTypes[".opus"] = "audio/opus";
    this->contentTypes[".otf"] = "font/otf";
    this->contentTypes[".png"] = "image/png";
    this->contentTypes[".pdf"] = "application/pdf";
    this->contentTypes[".php"] = "application/x-httpd-php";
    this->contentTypes[".ppt"] = "application/vnd.ms-powerpoint";
    this->contentTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    this->contentTypes[".rar"] = "application/vnd.rar";
    this->contentTypes[".rtf"] = "application/rtf";
    this->contentTypes[".sh"] = "application/x-sh";
    this->contentTypes[".svg"] = "image/svg+xml";
    this->contentTypes[".tar"] = "application/x-tar";
    this->contentTypes[".tif"] = "image/tiff";
    this->contentTypes[".tiff"] = "image/tiff";
    this->contentTypes[".ts"] = "video/mp2t";
    this->contentTypes[".ttf"] = "font/ttf";
    this->contentTypes[".txt"] = "text/plain";
    this->contentTypes[".vsd"] = "application/vnd.visio";
    this->contentTypes[".wav"] = "audio/wav";
    this->contentTypes[".weba"] = "audio/webm";
    this->contentTypes[".webm"] = "video/webm";
    this->contentTypes[".webp"] = "image/webp";
    this->contentTypes[".woff"] = "font/woff";
    this->contentTypes[".woff2"] = "font/woff2";
    this->contentTypes[".xhtml"] = "application/xhtml+xml";
    this->contentTypes[".xls"] = "application/vnd.ms-excel";
    this->contentTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    this->contentTypes[".xml"] = "application/xml";
    this->contentTypes[".xul"] = "application/vnd.mozilla.xul+xml";
    this->contentTypes[".zip"] = "application/zip";
    this->contentTypes[".3gp"] = "video/3gpp";
    this->contentTypes[".3g2"] = "video/3gpp2";
    this->contentTypes[".7z"] = "application/x-7z-compressed";
}

std::string ContentTypes::getMimeType(std::string extension) const
{
    std::map<std::string, std::string>::const_iterator it = contentTypes.find(extension);

    if (it != contentTypes.end())
    {
        return it->second;
    }
    else
    {
        return "application/octet-stream"; // MIME type padrão para "dados binários".
    }
}
