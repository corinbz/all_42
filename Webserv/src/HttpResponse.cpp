#include "../includes/HttpResponse.hpp"

HttpResponse::HttpResponse() : httpStatusCodes {
								{200, "OK"},
								{201, "Created"},
								{302, "Found"},
								{403, "Forbidden"},
								{404, "Not Found"},
								{405, "Method Not Allowed"},
								{408, "Request Timeout"},
								{413, "Payload Too Large"},
								{500, "Internal Server Error"},
								{501, "Not Implemented"}}
{}

HttpResponse::~HttpResponse() {}

void HttpResponse::processGET(const HttpRequest& req, ClientState& session)
{
	std::string uri = req.getRequestURI();
	static int img = 0;
	
    if(uri != "/get-images")
	{
        deliverFile(session, uri);
        return;
    }

	img++;
	static std::vector<std::string> imgs = {
		"/images/1.jpg",
		"/images/2.jpg",
		"/images/3.jpg",
		"/images/4.jpg"
	};
	
	std::string imgPath = session.serverConfig.rootDirectory + imgs[img % imgs.size()];
	std::ifstream file(imgPath.c_str());
	std::cout << "INFO: GET image " << imgPath << std::endl;
	if(!file)
	{
		std::cout << "\033[1;31mERROR:\033[0m 404, image not found " << imgPath << std::endl;
		buildGenericHttpResponse(404, "image not found");
		return; 
	}
	
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buildResponse(200, content, getMimeType(imgPath));
}

void HttpResponse::processDELETE(const HttpRequest& req, const ServerConfig& serverConfig)
{
	std::string uri = req.getRequestURI();
	std::cout << "INFO: method DELETE called" << std::endl;
	uri = serverConfig.rootDirectory + uri;

	int accessResult = access(uri.c_str(), F_OK);
	if(accessResult != 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m file not found " << uri << std::endl;
		buildGenericHttpResponse(404);
		return;
	}
	if(remove(uri.c_str()) == 0)
	{
		std::cout << "File deleted: " << uri << std::endl;
		buildGenericHttpResponse(200);
		return;
	}
	std::cout << "\033[1;31mERROR:\033[0m not able to delete file " << uri << std::endl;
	buildGenericHttpResponse(500);
}

void HttpResponse::processPOST(const HttpRequest& req, const ServerConfig& serverConfig)
{
	std::string uri = req.getRequestURI();
	std::string uploadPath = serverConfig.rootDirectory + uri + req.getUploadedFileName();
	int accessResult = access(uploadPath.c_str(), F_OK);
	if(accessResult == 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m this file was already uploaded, duplicates are not allowed " << uploadPath << std::endl;
		setHttpHeader("path ", uri + req.getUploadedFileName());
		setHttpStatusCode(302);
		setHttpBody("");
		return;
	}
	std::ofstream outputFile(uploadPath.c_str());

	if(!outputFile)
	{
		std::cout << "\033[1;31mERROR:\033[0m cant open this file " << uploadPath << std::endl;
		buildGenericHttpResponse(500);
		return;
	}

	outputFile.write(req.getHttpBody().c_str(), req.getHttpBody().size());
	outputFile.close();

	if(!outputFile.fail())
	{
		std::cout << "Your file was successfully uploaded " << uploadPath << std::endl;
		buildGenericHttpResponse(201, uploadPath);
		return;
	}
	std::cout << "\033[1;31mERROR:\033[0m failed to upload this file" << std::endl;
	buildGenericHttpResponse(500);
}

bool HttpResponse::isOnlySlashes(const std::string& requestPath)
{
	if(requestPath.empty())
		return true;
	size_t i = 0;
	while (i < requestPath.size())
	{
		if(requestPath[i] != '/')
			return false;
		++i;
	}
	return true;
}

void HttpResponse::routeRequest(HttpRequest& req, ClientState& session)
{
	std::string httpMethod = req.getHttpMethod();
	if(!validateRequestMethod(httpMethod, req.getRequestURI(), session.serverConfig))
	{
		buildGenericHttpResponse(405);
		std::cout << "\033[1;31mERROR:\033[0m HTTP method is not authorized - " << httpMethod << " " << req.getRequestURI() << std::endl;
		return;
	}

	std::string redirection = checkRedirect(req.getRequestURI(), session.serverConfig);
	if(!redirection.empty())
	{
		bool hasHttpPrefix = (redirection.substr(0, 7) == "http://" || redirection.substr(0, 8) == "https://");
		if(!hasHttpPrefix)
			redirection.insert(0, "http://");
		setHttpHeader("Location", redirection);
		setHttpStatusCode(302);
		setHttpBody("");
		return;
	}

	if(httpMethod == "GET")
		processGET(req, session);
	else if(httpMethod == "DELETE")
		processDELETE(req, session.serverConfig);
	else if(httpMethod == "POST")
		processPOST(req, session.serverConfig);
	else
	{
		buildGenericHttpResponse(501);
		std::cout << "HTTP method " << httpMethod << " not recognized" << std::endl;
	}
}

std::string HttpResponse::getLastFolderName(const std::string& requestPath)
{
	if(requestPath.empty())
		return ("");

	size_t slashPos = requestPath.find_last_of('/');
	if(requestPath.back() == '/')
		slashPos = requestPath.find_last_of('/', requestPath.length() - 2);
	if(slashPos == std::string::npos || slashPos == requestPath.length() - 1)
		return ("");

	size_t start = slashPos + 1;
	size_t end = requestPath.find('/', start);
	if(end == std::string::npos)
		end = requestPath.size();
	return requestPath.substr(start, end - start);
}

bool HttpResponse::deliverDefaultFile(const std::string& requestPath, const std::string& fullPath)
{
	std::string htmlPath = fullPath;
	if(htmlPath.back() != '/')
    	htmlPath += '/';
	htmlPath += getLastFolderName(requestPath) + ".html";

	std::ifstream file(htmlPath);
	if(file)
	{
		std::cout << "INFO: delivering " << htmlPath << std::endl << std::flush;
		std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		buildResponse(200, content, "text/html");
		return (true);
	}
		
	//std::cout << "\033[1;31mERROR:\033[0m failed to deliver " << htmlPath << std::endl << std::flush;
	return false;
}

bool HttpResponse::deliverIndex(const ServerConfig& serverConfig)
{
	std::string indexPath = serverConfig.rootDirectory;
	if(indexPath.back() != '/')
		indexPath += '/';
	indexPath += serverConfig.indexFile;

	std::ifstream indexFile(indexPath);
	if(indexFile)
	{
		std::cout << "INFO: delivering index " << indexPath << std::endl << std::flush;
		std::string content((std::istreambuf_iterator<char>(indexFile)), std::istreambuf_iterator<char>());
		buildResponse(200, content, "text/html");
		return true;
	}

	std::cout << "\033[1;31mERROR:\033[0m failed to deliver index.html" << std::endl << std::flush;
	return false;
}

void HttpResponse::deliverFile(const std::string& requestPath, const std::string& filePath)
{
	std::ifstream targetFile(filePath);
	if(targetFile)
	{
		std::cout << "INFO: delivering file " << filePath << std::endl << std::flush;
		std::string content((std::istreambuf_iterator<char>(targetFile)), std::istreambuf_iterator<char>());
		buildResponse(200, content, getMimeType(requestPath));
		return;
	}
	std::cout << "\033[1;31mERROR:\033[0m 404, file not found " << filePath << std::endl << std::flush;
	buildGenericHttpResponse(404, "something went worng :(");
}

void HttpResponse::deliverDirectoryListing(const std::string& requestPath, const std::string& fullPath)
{
	DIR* dir = opendir(fullPath.c_str());
	if(!dir)
	{
		std::cout << "\033[1;31mERROR:\033[0m code 404 - something went wrong, not able to open directory " << fullPath << std::endl;
		buildGenericHttpResponse(404, "This should never happen! HOW?!");
		return;
	}

	std::cout << "loading listening directory of " << fullPath << std::endl;
	struct dirent* entry;
	std::string content = "";

	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_name[0] == '.')
			continue;
		std::string name = entry->d_name;
		
        std::string sep = (requestPath.back() == '/') ? "" : "/";
        std::string link = requestPath + sep + name;

		content += "<li><a href='" + link + "'>" + name + "</a></li>";
	}

	closedir(dir);

	std::ostringstream stream;
	stream << "<!DOCTYPE html>"
		<< "<html lang=\"en\">"
		<< "<head>"
		<< "<meta charset=\"UTF-8\">"
		<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
		<< "<title>Index of " << requestPath << "</title>"
		<< "<link rel=\"stylesheet\" href=\"\\style.css\">"
		<< "<link rel=\"icon\" type=\"image/png\" href=\"coding.png\">"
		<< "</head>"
		<< "<body class=\"background\">"
		<< "<h1>Content of: " << requestPath << "</h1>"
		<< "<ul>" << content << "</ul>"
		<< "<button onclick=\"window.history.back()\" class=\"back-button\" style=\"margin:20px;\">BACK</button>"
		<< "</body>"
		<< "</html>";
	buildResponse(200, stream.str(), "text/html");
}

void HttpResponse::deliverDeletePage(const std::string& requestPath, const std::string& fullPath)
{
	DIR* dir = opendir(fullPath.c_str());
	if(!dir)
	{
		std::cout << "\033[1;31mERROR:\033[0m 404, not able to open " << fullPath << std::endl;
		buildGenericHttpResponse(404, "This should never happen. Yet it did. How?");
		return;
	}

	std::cout << "INFO: delivering DELETE page " << fullPath << std::endl;

	struct dirent* entry;
	std::string content = "";

	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_name[0] == '.')
			continue;
		std::string name = entry->d_name;
		std::string sep = (requestPath.back() == '/') ? "" : "/";
		std::string link = requestPath + sep + name;
		std::string deleteButton = "<button onclick=\""
								"fetch('" + link + "', {method: 'DELETE'})"
								".then(function(response) { "
								"if(response.ok) { "
								"window.location.reload();"
								"} else { "
								"alert('Delete failed with status: ' + response.status);"
								"}"
								"})"
								".catch(function(error) {"
								"alert('Network error or no response from server');"
								"})\">"
								"Delete</button>";
		content += "<li><a href='" + link + "'>" + name + "</a>" + deleteButton + "</li>";
	}

	closedir(dir);

	std::ostringstream stream;
	stream << "<!DOCTYPE html>"
		<< "<html lang=\"en\">"
		<< "<head>"
		<< "<meta charset=\"UTF-8\">"
		<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
		<< "<title>Delete page of " << requestPath << "</title>"
		<< "<link rel=\"stylesheet\" href=\"\\style.css\">"
		<< "<link rel=\"icon\" type=\"image/png\" href=\"coding.png\">"
		<< "</head>"
		<< "<body class=\"background\">"
		<< "<div class=\"error\">Delete page of " << requestPath << "</div>"
		<< "<hr>"
		<< "<div class=\"info\">" << content << "</div>"
		<< "<button onclick=\"window.history.back()\" class=\"back-button\" style=\"margin:20px;\">Back</button>"
		<< "</body>"
		<< "</html>";
	buildResponse(200, stream.str(), "text/html");
}

void HttpResponse::deliverFile(ClientState& client, const std::string& requestPath)
{
	std::string fullPath = client.serverConfig.rootDirectory + requestPath;
	struct stat path_stat;

	if(stat(fullPath.c_str(), &path_stat) != 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m 404, not able to recognise this path " << fullPath << std::endl;
		buildGenericHttpResponse(404, "These Are Not the Files You Are Looking For");
		return;
	}

	if(S_ISDIR(path_stat.st_mode))
	{
		if(isOnlySlashes(requestPath))
		{
			if(deliverIndex(client.serverConfig))
				return;
		}
		else if(deliverDefaultFile(requestPath, fullPath))
			return;
		else if(requestPath == "/uploads")
		{
			deliverDeletePage(requestPath, fullPath);
			return;
		}
		else if(client.serverConfig.directoryListing)
		{
			deliverDirectoryListing(requestPath, fullPath);
			return;
		}
		else
		{
			buildGenericHttpResponse(405, "something went wrong :(");
			return;
		}
	}

	if(S_ISREG(path_stat.st_mode))
	{
		deliverFile(requestPath, fullPath);
		return;	
	}

	std::cout << "\033[1;31mERROR:\033[0m 404, not able to recognise this path " << fullPath << std::endl;
	buildGenericHttpResponse(404, "These Are Not the Files You Are Looking For");
}

std::string HttpResponse::checkRedirect(const std::string& requestPath, const ServerConfig& serverConfig)
{
	size_t i = 0;
	const LocationConfig* mostSpecificMatch = NULL;

	while (i < serverConfig.locations.size())
	{
		const LocationConfig& loc = serverConfig.locations[i];
		if(requestPath.find(loc.locationPath) == 0)
		{
			if(!mostSpecificMatch || loc.locationPath.length() > mostSpecificMatch->locationPath.length())
				mostSpecificMatch = &loc;
		}
		++i;
	}

	if(mostSpecificMatch)
		return mostSpecificMatch->redirection;
	return "";
}

void HttpResponse::buildResponse(int code, const std::string& httpBody, std::string contentType)
{
	setHttpBody(httpBody);
	setHttpStatusCode(code);
	setHttpHeader("Content-Type", contentType);
	std::stringstream ss;
    ss << httpBody.size();
    setHttpHeader("Content-Length", ss.str());
}

std::string HttpResponse::toHttpString() const
{
	std::ostringstream outputStream;
	outputStream << "HTTP/1.1 " << this->httpStatusCode << " " << "\r\n";

	std::map<std::string, std::string>::const_iterator const_iter = this->httpHeaders.begin();
	while (const_iter != this->httpHeaders.end())
	{
		outputStream << const_iter->first << ": " << const_iter->second << "\r\n";
		++const_iter;
	}

	outputStream << "\r\n" << this->httpBody;
	return outputStream.str();
}

std::string HttpResponse::getMimeType(std::string requestURI)
{
	std::pair<std::string, std::string> mimeTypes[] = {
        {".css", "text/css"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".png", "image/png"},
        {".pdf", "application/pdf"},
        {".ico", "image/x-icon"}
    };

	size_t i = 0;
    while(i < sizeof(mimeTypes) / sizeof(mimeTypes[0]))
    {
        const std::string& ext = mimeTypes[i].first;
        if(requestURI.size() >= ext.size() && requestURI.compare(requestURI.size() - ext.size(), ext.size(), ext) == 0)
            return mimeTypes[i].second;
        ++i;
    }

	return "text/html";
}

void HttpResponse::buildGenericHttpResponse(int httpStatusCode, const std::string& message)
{
	std::ostringstream codeStream;
	codeStream << httpStatusCode;
	std::string code = codeStream.str();

	std::string codeMessage;
	if(httpStatusCodes.find(httpStatusCode) != httpStatusCodes.end())
    	codeMessage = httpStatusCodes.at(httpStatusCode);
	else
    	codeMessage = "Unknown Code In Map";

	std::ostringstream htmlStream;
	htmlStream << "<!DOCTYPE html>"
				<< "<html lang=\"en\">"
				<< "<head>"
				<< "<meta charset=\"UTF-8\">"
				<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
				<< "<title>Webserv - " << code << "</title>"
				<< "<link rel=\"stylesheet\" href=\"\\style.css\">"
				<< "<link rel=\"icon\" type=\"image/png\" href=\"coding.png\">"
				<< "</head>"
				<< "<body class=\"background\">"
				<< "<div class=\"error\">" << code << " - " << codeMessage << "</div>"
				<< "<hr>"
				<< "<div class=\"info\">" << message << "</div>"
				<< "<button onclick=\"window.history.back()\" class=\"back-button\">Back</button>"
				<< "</body>"
				<< "</html>";
	buildResponse(httpStatusCode, htmlStream.str(), "text/html");
}

bool HttpResponse::validateRequestMethod(const std::string& httpMethod, const std::string& requestURI, const ServerConfig& serverConfig)
{
	const LocationConfig* bestMatch = NULL;

	std::vector<LocationConfig>::const_iterator it = serverConfig.locations.begin();
	while (it != serverConfig.locations.end())
	{
		if(requestURI.find(it->locationPath) == 0) {
			if(!bestMatch || it->locationPath.length() > bestMatch->locationPath.length()) {
				bestMatch = &(*it);
			}
		}
		++it;
	}

	if(bestMatch) {
		if(bestMatch->allowedHttpMethods.empty())
			return false;

		std::vector<HttpMethods>::const_iterator iter = bestMatch->allowedHttpMethods.begin();
		while (iter != bestMatch->allowedHttpMethods.end())
		{
			if(httpMethod == requestTypeAsString(*iter))
				return true;
			++iter;
		}
	}

	return false;
}

// setters ---------------------

void HttpResponse::setHttpStatusCode(int code){this->httpStatusCode = code;}

void HttpResponse::setHttpHeader(const std::string& key, const std::string& value){this->httpHeaders[key] = value;}

void HttpResponse::setHttpBody(const std::string& httpBody){this->httpBody = httpBody;}

