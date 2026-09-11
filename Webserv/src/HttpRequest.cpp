#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest(){}

HttpRequest::HttpRequest(const std::string& rawRequest){readRawRequest(rawRequest);}

HttpRequest::~HttpRequest() {}

void HttpRequest::readRawRequest(const std::string& rawRequest)
{
	std::istringstream requestStream(rawRequest);
	std::string currentLine;
	std::getline(requestStream, currentLine);
	std::istringstream lineStream(currentLine);

	std::vector<std::string> parts;
    std::string token;
    while(lineStream >> token){parts.push_back(token);}

	if(parts.size() == 3)
	{
        this->httpMethod = parts[0];
        this->requestUri = parts[1];
        this->httpVersion = parts[2];
    }
	else
	{
		std::cout << "\033[1;31mERROR:\033[0m Bad HTTP request line - error code 1" << std::endl;
		exit(1);
    }
	extractHttpHeaders(requestStream);
	extractHttpBody(requestStream);
	std::cout << "http request received" << std::endl;
}

void HttpRequest::extractHttpHeaders(std::istringstream& requestStream)
{
	for(std::string currentLine; std::getline(requestStream, currentLine);)
	{
        if(currentLine.empty() || currentLine == "\r")
            break;

        std::size_t colonPos = currentLine.find(":");
        if(colonPos != std::string::npos)
		{
            std::string valuePart = trimWhitespace(currentLine.substr(colonPos + 1));
            this->httpHeaders.insert(std::pair<std::string, std::string>(currentLine.substr(0, colonPos), valuePart));
        }
    }
}

void HttpRequest::extractHttpBody(std::istringstream& requestStream)
{
	std::string typeHeader = this->httpHeaders["Content-Type"];

	if(typeHeader.find("multipart/form-data") != std::string::npos)
	{
        std::string boundary = getBoundary(typeHeader);
        if(!boundary.empty())
		{
            processMultipartData(requestStream, boundary);
            return;
        }
		std::cout << "issues with multipart/form-data" << std::endl;
        return;
    }
    std::string lengthHeader = this->httpHeaders["Content-Length"];
    if(!lengthHeader.empty())
	{
		int bodySize = std::stoi(lengthHeader);
        this->httpBody.resize(bodySize);
        for(int i = 0; i < bodySize; ++i)
		{
            char c;
            if(requestStream.get(c))
                this->httpBody[i] = c;
        }
    }
}

void HttpRequest::processMultipartData(std::istream& stream, const std::string& boundary)
{
    std::string boundaryMarker = "\r\n" + boundary;
    std::vector<char> boundaryVec(boundaryMarker.begin(), boundaryMarker.end());

    std::vector<char> tempBuffer;
    std::vector<char> fileBuffer;
    bool headerPhase = true;

    for(char ch; stream.get(ch);)
    {
        tempBuffer.push_back(ch);
        if(headerPhase)
        {
            if(tempBuffer.size() >= 4 && std::equal(tempBuffer.end() - 4, tempBuffer.end(), "\r\n\r\n"))
            {
                processMultipartHeaders(tempBuffer);
                headerPhase = false;
                tempBuffer.clear();
            }
        }
        else
        {
            if(tempBuffer.size() >= boundaryVec.size() && std::equal(boundaryVec.begin(), boundaryVec.end(), tempBuffer.end() - boundaryVec.size()))
            {
                fileBuffer.insert(fileBuffer.end(), tempBuffer.begin(), tempBuffer.end() - boundaryVec.size());
                break;
            }
        }
    }
    this->httpBody.assign(fileBuffer.begin(), fileBuffer.end());
}

void HttpRequest::processMultipartHeaders(const std::vector<char>& buffer)
{
    std::string rawHeaders(buffer.begin(), buffer.end() - 4);
    std::istringstream headerStream(rawHeaders);
    for (std::string line; std::getline(headerStream, line); ) {
        std::size_t pos = line.find("Content-Disposition:");
        if(pos != std::string::npos) {
            std::size_t fnameStart = line.find("filename=\"", pos);
            if(fnameStart != std::string::npos)
            {
                fnameStart += 10;
                std::size_t fnameEnd = line.find('"', fnameStart);
                if(fnameEnd != std::string::npos) {
                    this->uploadedFileName = line.substr(fnameStart, fnameEnd - fnameStart);
                }
            }
            continue; 
        }
        pos = line.find("Content-Type:");
        if(pos != std::string::npos)
        {
            std::size_t typeStart = line.find(':', pos);
            if(typeStart != std::string::npos) {
                this->fileMimeType = line.substr(typeStart + 2); // skip ": "
            }
        }
    }
}

std::string HttpRequest::getBoundary(const std::string& contentType) const
{
    const std::string key = "boundary=";
    std::size_t start = contentType.find(key);
    if(start == std::string::npos)
    {
        return "";
    }
	std::string boundary = contentType.substr(start + key.size());
	size_t end = boundary.find(";");
	if(end != std::string::npos)
    {
		boundary = boundary.substr(0, end);
	}
	return "--" + boundary;
}

// -----    getters :)

std::string HttpRequest::getHttpHeader(const std::string& headerName) const
{
    if(httpHeaders.count(headerName) > 0)
        return httpHeaders.at(headerName);
    return std::string{};
}
std::string HttpRequest::getHttpMethod() const {return this->httpMethod;}
std::string HttpRequest::getRequestURI() const {return this->requestUri;}
std::string HttpRequest::getHttpVersion() const {return this->httpVersion;}
std::string HttpRequest::getHttpBody() const {return this->httpBody;}
std::string HttpRequest::getUploadedFileName() const {return this->uploadedFileName;}
std::string HttpRequest::getFileMimeType() const {return this->fileMimeType;}

