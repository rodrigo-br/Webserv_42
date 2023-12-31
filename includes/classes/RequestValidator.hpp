#ifndef requestValidator_HPP
#define requestValidator_HPP

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>
# include "classes/Request.hpp"
# include "classes/Conf.hpp"
# include "ServerData.hpp"

class RequestValidator
{

	public:
		RequestValidator ();
		~RequestValidator();

		RequestValidator    		&requestValidator(ServerData &serverData, Request &request);
		HttpMethodEnum::httpMethod	getMethod(void) const;
		bool				        getPath(void) const;
		bool				        getHttpVersion(void) const;
		bool				        getBody(void) const;
		bool				        getHeader(std::string headerName) const;
		bool						getMethodAllowed(void) const;
		bool 						getServerName(void) const;
		bool						isDirectoryListing();
		bool						getBodySizeLimit(void) const;
		std::string					getErrorPage(int erro);
		std::string					getRoot(void) const;
		bool						getLocationRedirect(std::string locationName) const;
		void 						setBody(bool body);
		std::string					getRedirectedPath(std::string locationPath);

	private:
		HttpMethodEnum::httpMethod	methodValidator(Request& request);
		void 						pathValidator(ServerData &serverData, Request& request);
		void						bodyValidator(Request& request);
		void						bodySizeLimitValidator(ServerData &serverData, Request& request);
		void						httpVersionValidator(Request& request);
		void						serverNamesValidator(ServerData &serverData, Request& request);
		bool						isRootPath(const std::string& path, size_t	len);
		bool 						endsWithSlash(size_t position, size_t len);



    	void 						handleRootPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root);
    	void 						handlePathWithTrailingSlash(ServerData &serverData, Request& request, const std::string& path, const std::string& root);
    	void 						handleNonTrailingSlashPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root, size_t position);
    	void 						handleAssetsPath(Request& request, const std::string& path, const std::string& root, ServerData &serverData);
		void 						handleDirectoryListing(Request& request, std::string& path, const std::string& root, ServerData &serverData);
		HttpMethodEnum::httpMethod	_method;
		std::map<int, std::string>	_errorPages;
		bool                 		_path;
		bool                		_httpVersion;
		bool						_requestBody;
		bool						_serverName;
		bool						_isDirectoryListing;
		bool						_methodAllowed;
		bool						_bodySizeLimit;
		std::string					root;
		ServerData					_serverData;
};

#endif
