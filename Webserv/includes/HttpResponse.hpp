#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

#include<cstdio>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<signal.h>
#include<fcntl.h>
#include<map>
#include<string>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<ctime>

#include"HttpRequest.hpp"

class HttpResponse
{
	private:
		int httpStatusCode;
		std::map<std::string, std::string> httpHeaders;
		const std::map<int, std::string> httpStatusCodes;
		std::string httpBody;
	public:
		HttpResponse();
		~HttpResponse();
		void processGET(const HttpRequest& req, ClientState& session);
		void processPOST(const HttpRequest& req, const ServerConfig& serverConfig); 
		void processDELETE(const HttpRequest& request, const ServerConfig& serverConfig); 
		void deliverDeletePage(const std::string& uri, const std::string& fullPath); 
		void routeRequest(HttpRequest& request, ClientState& client);
		void buildGenericHttpResponse(int httpStatusCode, const std::string& message = "");
		void deliverFile(ClientState& client, const std::string& requestPath); 
		bool deliverIndex(const ServerConfig& serverConfig); 
		bool deliverDefaultFile(const std::string& requestPath, const std::string& fullPath);
		void deliverDirectoryListing(const std::string& uri, const std::string& fullPath);
		void buildResponse(int httpStatusCode, const std::string& httpBody, std::string contentType);
		bool isOnlySlashes(const std::string& requestPath); 
		std::string toHttpString() const; 
		std::string getMimeType(std::string requestURI);
		void deliverFile(const std::string& requestPath, const std::string& filePath);
		static bool validateRequestMethod(const std::string& httpMethod, const std::string& requestURI, const ServerConfig& serverConfig);
		std::string checkRedirect(const std::string& requestPath, const ServerConfig& serverConfig);
		std::string getLastFolderName(const std::string& uri);
		void setHttpStatusCode(int code);
		void setHttpHeader(const std::string& key, const std::string& value);
		void setHttpBody(const std::string& httpBody);
};

#endif