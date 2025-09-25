#ifndef UTILS_HPP
#define UTILS_HPP

#include<cctype>
#include<ctime>
#include<vector>
#include<map>
#include<sstream>
#include<limits>
#include<string>
#include<iostream>

enum HttpMethods
{
	GET,
	DELETE,
	POST,
};

struct LocationConfig
{
	std::string locationPath;
	std::string redirection;
	std::vector<HttpMethods> allowedHttpMethods;
};

struct ServerConfig
{
	std::string rootDirectory;
	bool directoryListing;
	std::vector<LocationConfig> locations;
	int keepAliveTimeout;
	int sendTimeout;
	std::string indexFile;
	std::string serverName;
	size_t maxBodySize;
	int listenPort;
};

struct ClientState
{
	// buffers
	std::string readBuffer;
	std::string writeBuffer;

	// request
	size_t totalRead = 0;
	size_t contentLength = 0;
	size_t headerEndIndex = 0;
	bool headersComplete = false;

	// connection info
	time_t lastActivity;
	bool keepAlive = false;
	bool closeConnection = false;
	int serverPort;

	//server configuration
	ServerConfig serverConfig;
	bool assignedConfig = false;

	// CGI related
	bool responding = false;
	bool killChild = false;
	bool forked = false;
	pid_t childPid;
	int cgiPipe[2];

	//http request related
	std::string method;
	std::string body;
};

struct HttpConfig
{
	int server_timeout_time;
	int keepAliveTimeout;
	std::vector<ServerConfig> serverConfigs;
};

std::string trimWhitespace(const std::string& str);
std::string requestTypeAsString(HttpMethods type);

#endif