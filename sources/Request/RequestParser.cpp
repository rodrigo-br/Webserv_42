#include "classes/RequestParser.hpp"
# include <sstream>

RequestParser::RequestParser(void) : _headers(), _method(""), _path(""), _httpVersion(""), _requestBody("") { }

RequestParser::~RequestParser(void) {}

void    RequestParser::parserHttpRequest(char *request)
{
	std::string			line;
	std::istringstream	iss(request);

	parseRequestStartLine(line, iss);
	parseRequestHeader(line, iss);
	parseRequestBody(line, iss);
    parseRequestPort();
    parserServerName();
    parseRquestQuery();
}

void    RequestParser::parseRquestQuery()
{	
    size_t queryStart = this->_path.find_first_of('?');
    if (queryStart != std::string::npos)
	{
		this->_query =  this->_path.substr(queryStart + 1);
	}
}

void    RequestParser::parseRequestPort()
{   
    std::string host = getHeader("Host");
    size_t      colonPos = host.find(':');
    if (colonPos != std::string::npos)
    {
        std::string portSubstring = host.substr(colonPos + 1);
        if (!portSubstring.empty())
        {
            this->_port = portSubstring;
            this->_portNumber = std::atoi(portSubstring.c_str());
        }
        
    }

}

void RequestParser::parserServerName(void)
{
	std::string host = getHeader("Host");
	this->_serverName = host.substr(0, host.find(':'));
}

void RequestParser::parseRequestBody(std::string& line, std::istringstream& iss)
{
    while (std::getline(iss, line)) 
    {
        this->_requestBody += line;
    }
}

void 	RequestParser::parseRequestHeader( std::string &line, std::istringstream &iss )
{
	while (std::getline(iss, line) && !line.empty())
    {
        if (line == "\r" || line == "\r\n")
        {
                break;
        }
        else
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                size_t lastNonCRLF = line.find_last_not_of("\r\n");
                if (lastNonCRLF != std::string::npos) 
                {
                    line = line.substr(0, lastNonCRLF + 1);
                    std::string headerName = line.substr(0, colonPos);
                    std::string headerValue = line.substr(colonPos + 2);
                    this->_headers[headerName] = headerValue;
                }
            }
        }
	}
}

void	RequestParser::parseRequestStartLine(std::string &line, std::istringstream &iss)
{
	if (std::getline(iss, line))
	{
        std::istringstream lineStream(line);
        lineStream >> this->_method >> _path >> this->_httpVersion;
    }
}

std::string RequestParser::getMethod(void) const
{
    return this->_method;
}

std::string RequestParser::getPath(void) const
{
    return this->_path;
}

std::string RequestParser::getHttpVersion(void) const
{
    return this->_httpVersion;
}

std::string RequestParser::getBody(void) const
{
    return this->_requestBody;
}

std::string RequestParser::getPort(void) const
{
    return this->_port;
}

int RequestParser::getPortNumber(void) const
{
    return this->_portNumber;
}

std::string RequestParser::getHeader(std::string headerName) const
{
    std::map<std::string, std::string>::const_iterator it = this->_headers.find(headerName);

    if (it != this->_headers.end())
    {
        return it->second;
    }
    else 
    {
        return "";
    }
}

std::string RequestParser::getQuery(void) const
{
    return this->_query;
}

std::string RequestParser::getServerName(void) const
{
    return this->_serverName;;
}

void RequestParser::setPath(std::string newPath)
{
    this->_path = newPath;
}

void RequestParser::setBody(std::string newBody)
{
    this->_requestBody = newBody;
}

std::string RequestParser::getFileExec(void) const
{
    return this->_fileExec;
}

void RequestParser::setFileExec(std::string fileExec)
{
    this->_fileExec = fileExec;
}