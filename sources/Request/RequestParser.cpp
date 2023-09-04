#include "classes/RequestParser.hpp"
# include <sstream>

RequestParser::RequestParser(void) : _headers(), _method(""), _path(""), _httpVersion(""), _requestBody("") { }

RequestParser::~RequestParser(void) {}

void    							RequestParser::parserHttpRequest(int fdConection)
{
    this->_fdClient = fdConection;	
	parseRequestStartLine();
	parseRequestHeader();
	parseRequestBody();
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

void RequestParser::parseChunkedBody(std::istringstream& iss)
{  
    std::string chunkSizeLine;
    std::string chunk;
    size_t chunkSize;

    while (std::getline(iss, chunkSizeLine))
    {
        std::stringstream chunkSizeStream(chunkSizeLine);
        chunkSizeStream >> std::hex >> chunkSize;
        if (chunkSize == 0)
        {
            break;
        }
        chunk.resize(chunkSize);
        iss.read(&chunk[0], chunkSize);
        std::string crlf;
        std::getline(iss, crlf);
        _requestBody += chunk;
    }
}

void parseMultipartFormDataBody(const std::string& boundary, std::string &tempLine)
{
    size_t boundaryPos = tempLine.find(boundary);
    if (boundaryPos == std::string::npos) 
    {
        return ; 
    }
    size_t contentStart = tempLine.find("\r\n\r\n", boundaryPos);
    if (contentStart == std::string::npos) 
    {
        return ; 
    }
    contentStart += 4;
    if (tempLine[contentStart] == '\r')
    {
        ++contentStart;
    }
    size_t contentEnd = tempLine.find(boundary, contentStart);
    if (contentEnd == std::string::npos) 
    {
        tempLine =  tempLine.substr(contentStart, contentEnd - contentStart);
        return ; 
    }
    while (contentEnd > contentStart && (tempLine[contentEnd - 1] == '\r' || tempLine[contentEnd - 1] == '\n' || tempLine[contentEnd - 1] == '-')) 
    {
        --contentEnd;
    }
    tempLine = tempLine.substr(contentStart, contentEnd - contentStart);
}

void RequestParser::parseRequestBody(void)
{

        // std::cout <<  "ola" << line << std::endl;

    // (void)line;
    // std::cout << std::endl <<  "parseRequestBody antes:" << _requestBody.length() << std::endl;

    // std::string transferEncoding = getHeader("Transfer-Encoding");
    // if (transferEncoding == "chunked")
    // {
    //     parseChunkedBody(iss);
    // }

    if (!getHeader("Content-Type").empty() && getHeader("Content-Type").find("multipart/form-data") != std::string::npos)
    {   
        std::string tempLine;

        Utils::readLineBody(this->_fdClient, tempLine, getContentLength());
        setFileName(tempLine);
        size_t pos = getHeader("Content-Type").find("boundary=", 0);
        if (pos != std::string::npos)
        {
            std::string boundary = getHeader("Content-Type").substr(pos + 9);
            parseMultipartFormDataBody(boundary, tempLine);
        }
        this->_requestBody += tempLine;
    }
}

void 	RequestParser::parseRequestHeader(void)
{
    std::string line;

    while (true)
    {
        Utils::readLine(_fdClient, line, CRLF);
        if (line == CRLF || line.empty())
        {
            break;
        }
        else
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                size_t lastNonCRLF = line.find_last_not_of(CRLF);
                if (lastNonCRLF != std::string::npos) 
                {
                    line = line.substr(0, lastNonCRLF + 1);
                    std::string headerName = line.substr(0, colonPos);
                    std::string headerValue = line.substr(colonPos + 2);
                    this->_headers[headerName] = headerValue;

                }
            }
        }
        this->_request += line + "\n";
    }
}

void	RequestParser::parseRequestStartLine(void)
{
    std::string line;

    Utils::readLine(_fdClient, line, CRLF);
	if (!line.empty())
	{
        std::istringstream lineStream(line);
        lineStream >> this->_method >> this->_path >> this->_httpVersion;
        this->_request += line +  "\n";
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

std::string RequestParser::getFileName(void) const
{
    return this->_fileName;
}


std::string RequestParser::getRequest(void) const
{
    return this->_request;
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

void RequestParser::setFileName(std::string line)
{

    if (line.find("filename=\"") != std::string::npos)
    {
        size_t filenameEndPos = line.find("\"", line.find("filename=\"") + 10);
        if (filenameEndPos != std::string::npos)
        {
            _fileName = line.substr(line.find("filename=\"") + 10, filenameEndPos - (line.find("filename=\"") + 10));
        }
    }
    
}

int RequestParser::getContentLength() const
{
    std::string contentLengthStr = getHeader("Content-Length");
    
    if (!contentLengthStr.empty())
    {
        return atol(contentLengthStr.c_str());
    }
    return 0;
}