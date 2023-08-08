#ifndef REQUEST_VALIDATOR_HPP
#define REQUEST_VALIDATOR_HPP

# include <string>
# include "enums/HttpMethodsEnum.hpp"
# include <iostream>
# include <map>
# include "classes/Request.hpp" 
# include "classes/Conf.hpp"

class RequestValidator
{

	public:
		RequestValidator ();
		~RequestValidator();

		RequestValidator    		&request_validator( Conf &conf, Request &request);
		HttpMethodEnum::httpMethod	get_method(void) const;
		bool				        get_path(void) const;
		bool				        get_http_version(void) const;
		bool				        get_body(void) const;
		bool				        get_header(std::string header_name) const;

	private:
		HttpMethodEnum::httpMethod	method_validator(Request& request);
		void 						path_validator(Conf& conf, Request& request);
		void						body_validator(Request& request);
		void						http_version_validator(Request& request);
		bool isRootPath(const std::string& path, size_t	len);
		bool 		endsWithSlash(size_t position, size_t len);


    	void handleRootPath(Conf& conf, Request& request, const std::string& path, const std::string& root);
    	void handlePathWithTrailingSlash(Conf& conf, Request& request, const std::string& path, const std::string& root);
    	void handleNonTrailingSlashPath(Conf& conf, Request& request, const std::string& path, const std::string& root, size_t position);
    	void handleAssetsPath(Request& request, const std::string& path, const std::string& root);
		HttpMethodEnum::httpMethod	_method;
		bool                 		_path;
		bool                		_http_version;
		bool						_requestBody;
};

#endif
