#include "../includes/ConfigHandler.hpp"

ConfigHandler::ConfigHandler()
{
	this->httpConfig.server_timeout_time = -1; // convention in C/C++, set invalid value
}

ConfigHandler::~ConfigHandler(){}

HttpConfig& ConfigHandler::getConfig()
{
	return this->httpConfig;
}

void ConfigHandler::processConfigFile(std::string configPath)
{
	std::ifstream file(configPath.c_str());
	if(!file)
	{
		std::cout << "\033[1;31mERROR:\033[0m Not able to open config file" << std::endl;
		exit(1);
	}
	std::string currentLine;
	while(getline(file, currentLine))
	{
		currentLine = trimWhitespace(currentLine);
		if(currentLine.empty() || currentLine[0] == '#')
			continue;
		if(currentLine == "http {")
			readHttpBlock(file, currentLine);
		else
		{
			std::cout << "Unexpected line: " << currentLine << std::endl;
			exit(1);
		}
	}
	file.close();
	verifyConfiguration();
	std::cout << "Config file was successfuly parsed" << std::endl;
}

void ConfigHandler::setupDefaultServerConfig(ServerConfig& serverConfig)
{
	required.clear();
    defined.clear();
    required = {"index", "root", "server_name", "listen"};
    serverConfig.maxBodySize = 200;
    serverConfig.directoryListing = false;
}

void ConfigHandler::readHttpBlock(std::ifstream& configFile, std::string& currentLine)
{
	this->scopeStack.push("HTTP");
	while(!scopeStack.empty())
	{
		if(!getline(configFile, currentLine))
		{
			std::cout << "\033[1;31mERROR:\033[0m ConfFile is missing - '}'" << std::endl;
			exit(1);
		}
		currentLine = trimWhitespace(currentLine);
		if(currentLine.empty() || currentLine[0] == '#')
			continue;

		std::string key, value;
		parseKeyValuePair(currentLine, key, value);
		
		if(currentLine == "}")
			scopeStack.pop();
		else if(key == "server_timeout_time")
		{
			if(value.empty())
			{
				std::cout << "\033[1;31mERROR:\033[0m server_timeout_time value is missing" << std::endl;
				exit(1);
			}
			httpConfig.server_timeout_time = stringToInt(value);
		}
		else if(currentLine == "server {")
		{
			ServerConfig serverConfig;
			setupDefaultServerConfig(serverConfig);
			readServerBlock(configFile, currentLine, serverConfig);
			httpConfig.serverConfigs.push_back(serverConfig);
		}
		else
		{
			std::cout << "\033[1;31mERROR:\033[0m unexpected http line: " << currentLine << std::endl;
			exit(1);
		}
	}
}

void ConfigHandler::readServerBlock(std::ifstream& configFile, std::string& currentLine, ServerConfig& serverConfig)
{
	scopeStack.push("SERVER");
	while(!scopeStack.empty())
	{
		getline(configFile, currentLine);
		currentLine = trimWhitespace(currentLine);
		if(currentLine.empty() || currentLine[0] == '#')
			continue;

		if(currentLine == "}")
		{
			scopeStack.pop();
			break;
		}
		else if(currentLine.find("location") == 0)
		{
			LocationConfig locConfig;
			readLocationBlock(configFile, currentLine, locConfig);
			serverConfig.locations.push_back(locConfig);
		}
		else
			readServerSettings(currentLine, serverConfig);
	}
	if(!required.empty())
	{
		std::ostringstream oss;
		for (size_t i = 0; i < required.size(); ++i)
		{
			if(i != 0)
				oss << " ";
			oss << required[i];
		}
		std::string missingKeys = oss.str();
		std::cout << "missing server directive: " << missingKeys << std::endl;
		exit(1);
	}
}

void ConfigHandler::readServerSettings(std::string& currentLine, ServerConfig& serverConfig)
{
	std::string key;
	std::string value;
	parseKeyValuePair(currentLine, key, value);

	if(key.empty() || value.empty())
	{
		std::cout << "\033[1;31mERROR:\033[0m Not able to find key or value - error code 4" << std::endl;
		exit(4);
	}
	if(std::find(this->defined.begin(), this->defined.end(), key) != this->defined.end())
	{
		std::cout << "\033[1;31mERROR:\033[0m key duplicate - error code 4" << std::endl;
		exit(4);	
	}
	if(key == "index")
		serverConfig.indexFile = value;
	else if(key == "server_name")
		serverConfig.serverName = value;
	else if(key == "listen")
		serverConfig.listenPort = stringToInt(value);
	else if(key == "keepalive_timeout")
		serverConfig.keepAliveTimeout = stringToInt(value);
	else if(key == "send_timeout")
		serverConfig.sendTimeout = stringToInt(value);
	else if(key == "max_body_size")
		serverConfig.maxBodySize = stringToInt(value);
	else if(key == "root")
		serverConfig.rootDirectory = value;
	else if(key == "directory_listing")
		serverConfig.directoryListing = (value == "true");
	else
	{
		std::cout << "\033[1;31mERROR:\033[0m Unknown key - error code 4" << std::endl;	
		exit(4);
	}
	this->required.erase(std::remove(this->required.begin(), this->required.end(), key), this->required.end());
	this->defined.push_back(key);
}

void ConfigHandler::readLocationBlock(std::ifstream& configFile, std::string& currentLine, LocationConfig& locConfig)
{
	this->scopeStack.push("LOCATION");
	std::string key, value;
	
	validateLocationPath(currentLine, locConfig);
	while(!this->scopeStack.empty())
	{
		getline(configFile, currentLine);
		currentLine = trimWhitespace(currentLine);
		if(currentLine.empty() || currentLine[0] == '#')
			continue;
		if(currentLine == "}")
		{
			this->scopeStack.pop();
			break;
		}
		else
		{
			parseKeyValuePair(currentLine, key, value);
			if(key == "request_types")
			{
				std::istringstream iss(value);
				std::string requestType;
				while(iss >> requestType)
				{
					HttpMethods type = parseRequestType(trimWhitespace(requestType));
					locConfig.allowedHttpMethods.push_back(type);
				}
			}
			else if(key == "redirection")
				locConfig.redirection = value;
			else
			{
				std::cout << "\033[1;31mERROR:\033[0m Unknown key - error code 5" << std::endl;	
				exit(5);
			}
		}
	}
}

void ConfigHandler::validateLocationPath(std::string& currentLine, LocationConfig& locConfig)
{
	std::string key;
	parseKeyValuePair(currentLine, key, locConfig.locationPath);

	size_t bracePos = locConfig.locationPath.find('{');
	if(bracePos != std::string::npos)
	{
		locConfig.locationPath = locConfig.locationPath.substr(0, bracePos);
		locConfig.locationPath = trimWhitespace(locConfig.locationPath);
	}
	std::istringstream iss(currentLine);
	std::vector<std::string> parts;
	std::string part;
	for (std::istringstream iss(currentLine); iss >> part;)
    	parts.push_back(part);
	if(parts.size() != 3 || locConfig.locationPath.empty())
	{
		std::cout << "\033[1;31mERROR:\033[0m Location path is invalid - error code 6" << std::endl;
		exit(6);
	}
}

void ConfigHandler::verifyConfiguration()
{
	if(this->httpConfig.server_timeout_time == -1)
	{
		std::cout << "\033[1;31mERROR:\033[0m server_timeout_time is missing/invalid - error code 7" << std::endl; 
		exit(7);
	}
	if(this->httpConfig.serverConfigs.size() == 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m server config is missing/invalid" << std::endl;
		exit(7);
	}
}

HttpMethods ConfigHandler::parseRequestType(const std::string& str)
{
	if(str == "GET")
		return GET;

	if(str == "DELETE")
		return DELETE;

	if(str == "POST")
		return POST;

	std::cout << "\033[1;31mERROR:\033[0m request type unsupported... shuting down" << std::endl;
	exit(1);
}

void ConfigHandler::parseKeyValuePair(const std::string& line, std::string& key, std::string& value)
{
	key.clear();
	value.clear();

    size_t keyBegin = line.find_first_not_of(" \t");
    if(keyBegin == std::string::npos)
        return;

    size_t keyFinish = line.find_first_of(" \t", keyBegin);
    key = trimWhitespace(line.substr(keyBegin, keyFinish - keyBegin));

    size_t valueBegin = line.find_first_not_of(" \t", keyFinish);
    if(valueBegin != std::string::npos)
        value = trimWhitespace(line.substr(valueBegin));
}

int ConfigHandler::stringToInt(const std::string& str)
{
	if(str.empty())
	{
		std::cout << "\033[1;31mERROR:\033[0m not able to convert string to int, string is empty" << std::endl;
		exit(5);
	}

	std::istringstream iss(str);
	long long val;
	iss >> val;

	if(iss.fail() || !iss.eof() || val < 0 || val > std::numeric_limits<int>::max())
	{
		std::cout << "\033[1;31mERROR:\033[0m not able to convert string to int > " << str << std::endl;
		exit(5);
	}
	return static_cast<int>(val);
}
