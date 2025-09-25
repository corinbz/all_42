#ifndef CONFIGHANDLER_HPP
#define CONFIGHANDLER_HPP

#include<sstream>
#include<stack>
#include<limits>
#include<algorithm>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>

#include "utils.hpp"

class ConfigHandler
{
	private:
		std::vector<std::string> required;
		std::vector<std::string> defined;
		HttpConfig httpConfig;
		std::stack<std::string> scopeStack;

		void readHttpBlock(std::ifstream& configFile, std::string& currentLine);
		void readServerBlock(std::ifstream& configFile, std::string& currentLine, ServerConfig& serverConfig);
		void readServerSettings(std::string& line, ServerConfig& serverConfig);
		void readLocationBlock(std::ifstream& configFile, std::string& line, LocationConfig& locConfig);
		void validateLocationPath(std::string& line, LocationConfig& locConfig);
		void setupDefaultServerConfig(ServerConfig& serverConfig);
		HttpMethods parseRequestType(const std::string& str);
		void parseKeyValuePair(const std::string& line, std::string& key, std::string& value);
		int stringToInt(const std::string& str);
	public:
		ConfigHandler();
		~ConfigHandler();
		void processConfigFile(std::string configFilePath);
		void verifyConfiguration();
		HttpConfig& getConfig();
};

#endif