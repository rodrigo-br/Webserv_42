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

void RequestParser::parseChunkedBody(std::istringstream& iss)
{
   
    std::string chunkSizeLine;
    std::string chunk;
    size_t chunkSize;

        std::cout<< "aaaaaaaaaaaaaaaaaaaa  ="<<  std::endl << chunk << std::endl << std::endl;

    // Continue lendo os chunks até encontrar um chunk com tamanho zero
    while (std::getline(iss, chunkSizeLine))
    {
        std::stringstream chunkSizeStream(chunkSizeLine);
        chunkSizeStream >> std::hex >> chunkSize;
        
        if (chunkSize == 0)
        {
        std::cout<< "aaaaaaaaaaaaaaaaaaaa  ="<<  std::endl << chunk << std::endl << std::endl;

            break;
        }

        // Lê o chunk atual
        chunk.resize(chunkSize);
        iss.read(&chunk[0], chunkSize);

        // Descarta o CRLF após o chunk
        std::string crlf;
        std::getline(iss, crlf);

        // Adiciona o chunk ao corpo da requisição
        std::cout<< "chunkkkkkkkkkkkkkkkke  ="<<  std::endl << chunk << std::endl << std::endl;
        _requestBody += chunk;
    }
}


void RequestParser::parseContentLengthBody(std::istringstream& iss)
{
    std::string line;
    size_t contentLength = getContentLength(); // Implemente essa função

    while (contentLength > 0 && std::getline(iss, line))
    {
        this->_requestBody += line + "\r\n"; // Adicione o tamanho dos caracteres de nova linha
        contentLength -= (line.size() + 2); // Tamanho da linha + 2 para os caracteres de nova linha
    }
    // Finalize o processamento do corpo se necessário
}

int RequestParser::getContentLength() const
{
    std::string contentLengthStr = getHeader("Content-Length");
    
    if (!contentLengthStr.empty())
    {
        return atoi(contentLengthStr.c_str());
    }
    
    return 0;
}

void RequestParser::parseRequestBody(std::string& line, std::istringstream& iss)
{
    // while (std::getline(iss, line)) 
    // {
    //     this->_requestBody += line;
    // }
    (void)line;
    std::string transferEncoding = getHeader("Transfer-Encoding");
    if (transferEncoding == "chunked")
    {
        parseChunkedBody(iss);
    }

    else if (!getHeader("Content-Length").empty())
    {
        parseContentLengthBody(iss);
        std::cout <<  std::endl<< "entrou no contrenteeeeeeeeeeee "<< std::endl <<  std::endl;
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