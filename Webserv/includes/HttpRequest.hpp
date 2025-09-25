#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include<algorithm>
#include<fstream>
#include<vector>
#include"utils.hpp"
#include<string>
#include<sstream>
#include<iostream>
#include<map>

class HttpRequest
{
	private:
		std::string httpMethod;
		std::string requestUri;
		std::string httpVersion;
		std::map<std::string, std::string> httpHeaders;
		std::string httpBody;
		std::string uploadedFileName;
		std::string fileMimeType;

		void extractHttpHeaders(std::istringstream& requestStream);
		void extractHttpBody(std::istringstream& requestStream);
		void processMultipartData(std::istream& stream, const std::string& boundary);
		void processMultipartHeaders(const std::vector<char>& buffer);
		std::string getBoundary(const std::string& contentType) const;
	public:
		HttpRequest();
		HttpRequest(const std::string& request);
		~HttpRequest();
		void readRawRequest(const std::string& rawRequest);

		std::string getHttpMethod() const;
		std::string getRequestURI() const;
		std::string getHttpVersion() const;
		std::string getHttpBody() const;
		std::string getUploadedFileName() const;
		std::string getFileMimeType() const;
		std::string getHttpHeader(const std::string& headerName) const;
	};
	
#endif