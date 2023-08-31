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
		bool 						getServerName(void) const;
		bool						getRequiredMethodAllowed(void) const;
		bool						isDirectoryListing();
		std::string					getRoot(void) const;

		void 						setBody(bool body);

	private:
		HttpMethodEnum::httpMethod	methodValidator(Request& request);
		void 						pathValidator(ServerData &serverData, Request& request);
		void						bodyValidator(Request& request);
		void						httpVersionValidator(Request& request);
		void						serverNamesValidator(ServerData &serverData, Request& request);
		void 						fileExecValidator(std::string root, Request& request);
		bool						isRootPath(const std::string& path, size_t	len);
		bool 						endsWithSlash(size_t position, size_t len);



		void 						handleAllowedMethods(Request& request, std::string& path, ServerData &serverData);
    	void 						handleRootPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root);
    	void 						handlePathWithTrailingSlash(ServerData &serverData, Request& request, const std::string& path, const std::string& root);
    	void 						handleNonTrailingSlashPath(ServerData &serverData, Request& request, const std::string& path, const std::string& root, size_t position);
    	void 						handleAssetsPath(Request& request, const std::string& path, const std::string& root);
		void 						handleDirectoryListing(Request& request, std::string& path, const std::string& root, ServerData &serverData);
		HttpMethodEnum::httpMethod	_method;
		bool                 		_path;
		bool                		_httpVersion;
		bool						_requestBody;
		bool						_serverName;
		bool						_isDirectoryListing;
		bool						_requiredMethodAllowed;
		std::string					root;
};

#endif
