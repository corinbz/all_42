#include "../includes/Server.hpp"

bool server_running;

Server::Server(const HttpConfig& config): httpConfig(config){}

Server::~Server()
{
	std::cout << "Shutting down the server" << std::endl;
	size_t i = 0;
	while (i < this->fds.size())
	{
		disconectClient(this->fds[i].fd);
		i++;
	}
}

bool Server::checkServerFd(int fd)
{
	return std::find(this->server_fds.begin(), this->server_fds.end(), fd) != this->server_fds.end();
}

ServerConfig& Server::selectServerConfig(std::string &hostName, int port)
{
	size_t pos = hostName.find(":");

	if(pos != std::string::npos)
		hostName = hostName.substr(0, pos);
	bool backupReady = false;

	std::vector<ServerConfig>::iterator firstPortMatch;
	std::vector<ServerConfig>::iterator iter = this->httpConfig.serverConfigs.begin();
	while(iter != this->httpConfig.serverConfigs.end())
    {
        if(!backupReady && iter->listenPort == port)
        {
			firstPortMatch = iter;
            backupReady = true;
        }
        if(iter->listenPort == port && iter->serverName == hostName)
            return *iter;

        ++iter;
    }

	if(backupReady)
		return *firstPortMatch;
	std::cout << "\033[1;31mERROR:\033[0m invalid server config...shuting down!" << std::endl;
	exit(1);
}

void Server::disconectClient(int fd)
{
	close(fd);
	std::vector<struct pollfd>::iterator it = this->fds.begin();
	while (it != this->fds.end())
	{
		if(it->fd == fd)
			it = this->fds.erase(it);
		else
			++it;
	}
	std::vector<int>::iterator it_s = this->server_fds.begin();
	while(it_s != this->server_fds.end())
	{
		if(*it_s == fd)
			it_s = this->server_fds.erase(it_s);
		else
			++it_s;
	}
	std::map<int, ClientState>::iterator it_c = this->clientStates.find(fd);
	if(it_c != this->clientStates.end())
		this->clientStates.erase(it_c);
}

void Server::handlePollIn(pollfd &fd)
{
	std::cout << "INFO: socket " << fd.fd << " received a request" << std::endl;
	if(checkServerFd(fd.fd))
	{
		handleNewConnection(fd.fd);
		return ;
	}
	ClientState &client = clientStates[fd.fd];
	time(&client.lastActivity);
	client.responding = true;
	bool hasRequest = handleInData(fd.fd);
	if(hasRequest)
	{
		fd.events = fd.events | POLLOUT;
		handleClientRequest(fd.fd);
	}
}

void Server::handlePollOut(pollfd &fd)
{
	ClientState &client = clientStates[fd.fd];
	if(clientStates[fd.fd].forked) 
	{
		handleCgiOut(checkCgiStatus(client), fd.fd);
		return ;
	}
	std::cout << "INFO: Answering to socket " << fd.fd << std::endl;
	time(&client.lastActivity);
	respondToClient(fd);
}

void Server::handleClientActivity(pollfd &fd, size_t &index)
{
    if (fd.revents & POLLOUT)
        handlePollOut(fd);

    time_t now;
    time(&now);
    ClientState &client = clientStates[fd.fd];

    if (client.assignedConfig && client.responding && difftime(now, client.lastActivity) > client.serverConfig.sendTimeout)
	{
        std::cout << "timeout on socket" << std::endl;
        client.killChild = true;
    }
    if (client.assignedConfig && difftime(now, client.lastActivity) > client.serverConfig.keepAliveTimeout)
	{
        std::cout << "keep alive timeout" << std::endl;
        client.closeConnection = true;
    }
    if (client.closeConnection)
	{
        disconectClient(fd.fd);
        index--;
    }
}

void Server::handleEvents()
{
    for (size_t i = 0; i < fds.size(); i++)
	{
        pollfd current = fds[i]; // make a copy, don’t hold reference

        if (current.revents & (POLLERR | POLLHUP | POLLNVAL))
		{
            if (current.revents & (POLLERR))
				std::cout << "WARRNING: POLLERR ops failed on socket " << current.fd << std::endl;
			if (current.revents & (POLLHUP))
				std::cout << "WARRNING: POLLERR connection closed on socket " << current.fd << std::endl;
			if (current.revents & (POLLNVAL))
				std::cout << "WARRNING: POLLNVAL not able to open fd or invalid socket " << current.fd << std::endl;
			clientStates[current.fd].closeConnection = true;
            continue;
        }
        if (current.revents & POLLIN)
            handlePollIn(fds[i]);

        if (!checkServerFd(current.fd))
            handleClientActivity(fds[i], i);
    }
}

void Server::launch()
{
	if(this->fds.size() == 0)
	{
			std::cout << "\033[1;31mERROR:\033[0m not possible to run poll()" << std::endl;
			return ;
	}
	server_running = true;
	signal(SIGINT, [](int){ server_running = false; });
	while(server_running)
	{
		if (poll(&this->fds[0], this->fds.size(), this->httpConfig.server_timeout_time) < 0)
		{
			switch (errno)
			{
				case EBADF:
					std::cout << "\033[1;31mERROR:\033[0m poll failed - EBADF" << std::endl;
					break;
				case EINTR:
					std::cout << "\033[1;31mERROR:\033[0m poll failed - EINTR" << std::endl;
					break;
				case EINVAL:
					std::cout << "\033[1;31mERROR:\033[0m poll failed - EINVAL" << std::endl;
					break;
				case ENOMEM:
					std::cout << "\033[1;31mERROR:\033[0m poll failed - ENOMEM" << std::endl;
					break;
				default:
					std::cout << "\033[1;31mERROR:\033[0m poll failed - Unknown error" << std::endl;
			break;
	}
			continue;
		}
		handleEvents();
	}
}

void Server::initSockets()
{
	std::cout << "init sockets in progress..." << std::endl;
	std::vector<int> ports;

    size_t i = 0;
    while(i < this->httpConfig.serverConfigs.size())
	{
        int port = this->httpConfig.serverConfigs[i].listenPort;

        // Check if port already exists
        size_t j = 0;
        bool exists = false;
        while(j < ports.size())
		{
            if(ports[j] == port)
			{
                exists = true;
                break;
            }
            j++;
        }
        if(exists)
		{
            i++;
            continue;
        }
        int sockfd = setupSockets(port);
        if(sockfd >= 0)
		{
            ports.push_back(port);
            struct pollfd pfd = {sockfd, POLLIN, 0};
            this->fds.push_back(pfd);
            this->server_fds.push_back(sockfd);
            this->serverConfigs[sockfd] = this->httpConfig.serverConfigs[i];
        }
        i++;
    }
}


int Server::createSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;
    return sockfd;
}

bool Server::setSocketOptions(int sockfd)
{
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) return false;
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK | FD_CLOEXEC) < 0) return false;
    return true;
}

bool Server::bindSocket(int sockfd, int port)
{
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    return bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == 0;
}

int Server::setupSockets(int port)
{
	int sockfd = createSocket();
    if (sockfd < 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m not able to create socket on port " << port << std::endl;
		return -1;
	}

	if(!setSocketOptions(sockfd))
	{
        disconectClient(sockfd);
		std::cout << "\033[1;31mERROR:\033[0m not able to set socket options" << std::endl;
        return -1;
    }

    if (!bindSocket(sockfd, port))
	{
        disconectClient(sockfd);
		std::cout << "\033[1;31mERROR:\033[0m not able to bind socket to port " << port << std::endl;
        return -1;
    }

    if (listen(sockfd, SOMAXCONN) < 0)
	{
        disconectClient(sockfd);
		std::cout << "\033[1;31mERROR:\033[0m socket " << sockfd << ", failed to listen" << std::endl;
        return -1;
    }
	std::cout << "SUCCESS: Socket " << sockfd << " on port " << port << std::endl;
    return sockfd;
}

int Server::acceptClientSocket(int server_fd)
{
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m was not able to accept new connection..." << std::endl;
        return -1;
    }
    return client_fd;
}

void Server::handleNewConnection(int server_fd)
{
    int client_fd = acceptClientSocket(server_fd);
    if(client_fd < 0) return ;
		
	fcntl(client_fd, F_SETFL, O_NONBLOCK | FD_CLOEXEC);
	this->clientStates[client_fd] = ClientState();
	time(&this->clientStates[client_fd].lastActivity);
	this->clientStates[client_fd].serverPort = this->serverConfigs[server_fd].listenPort;

	struct pollfd new_pfd = {client_fd, POLLIN, 0};
	this->fds.push_back(new_pfd);
	std::cout << "Server " << server_fd << "accepted connection on socket " << client_fd << std::endl;
}

void Server::parseRequestHeaders(int fd)
{
	ClientState& client = clientStates[fd];
    size_t headerTerm = client.readBuffer.find("\r\n\r\n");
    if (headerTerm == std::string::npos)
        return;

    client.headersComplete = true;
    client.headerEndIndex = headerTerm + 4;

    size_t startPos = client.readBuffer.find("Content-Length: ");
    if(startPos != std::string::npos)
	{
        startPos += 16;
        size_t endPos = client.readBuffer.find("\r\n", startPos);
        std::string lengthStr = client.readBuffer.substr(startPos, endPos - startPos);
        client.contentLength = std::stoul(lengthStr);
        client.totalRead = client.readBuffer.length() - client.headerEndIndex;
    }
	else
        client.contentLength = 0;

    startPos = client.readBuffer.find("Host: ");
    std::string hostName;
    if(startPos != std::string::npos)
	{
        startPos += 6;
        size_t endPos = client.readBuffer.find("\r\n", startPos);
        hostName = client.readBuffer.substr(startPos, endPos - startPos);
    }
    client.serverConfig = selectServerConfig(hostName, client.serverPort);
    client.assignedConfig = true;
}

bool Server::handleInData(int fd)
{
    const size_t buff_size = 16384;
    char dataBuffer[buff_size];
    std::memset(dataBuffer, 0, sizeof(dataBuffer));

    ssize_t receiveBytes = recv(fd, dataBuffer, buff_size, 0);

	if(receiveBytes == 0)
	{
    	this->clientStates[fd].closeConnection = true;
		return false;
	}
    if(receiveBytes < 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m recv() failed" << std::endl;
        this->clientStates[fd].closeConnection = true;
		return false;
    }
	this->clientStates[fd].readBuffer.append(dataBuffer, receiveBytes);
	if(!this->clientStates[fd].headersComplete)
        parseRequestHeaders(fd);
	else
		this->clientStates[fd].totalRead += receiveBytes;
	if(this->clientStates[fd].headersComplete && this->clientStates[fd].totalRead == this->clientStates[fd].contentLength)
	{
		this->clientStates[fd].totalRead = 0;
		this->clientStates[fd].headersComplete = false;
		return true;
	}
    return false;
}

std::string Server::executeCGI(ClientState& client, std::string& path)
{
	if(client.forked)
        return checkCgiStatus(client);

	std::cout << "INFO: executin CGI..." << std::endl;
    if(pipe(client.cgiPipe) == -1)
	{
		std::cout << "\033[1;31mERROR:\033[0m failed to create pipe" << std::endl;
        return "500 Server Error";
    }

    client.childPid = fork();
    if(client.childPid < 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m failed forking" << std::endl;
        close(client.cgiPipe[0]);
        close(client.cgiPipe[1]);
        return "500 Server Error";
    }
    if(client.childPid == 0)
	{
        setupAndExecChild(client, path); // child process executes CGI
        return "500 Server Error";
    }

    close(client.cgiPipe[1]); // Close write end of pipe
    client.forked = true;

    return checkCgiStatus(client);
}

void Server::handleCgiOut(std::string str, int fd)
{
	if (str.empty())
        return ;

	HttpResponse response;
	if(str == "timeout_cgi" || str == "error_cgi_script" || str == "server_error")
		response.buildGenericHttpResponse(500, str);
	else
		response.buildResponse(200, str, "text/html");
	this->clientStates[fd].writeBuffer = response.toHttpString();
	this->clientStates[fd].readBuffer.clear();
	this->clientStates[fd].forked = false;
}


std::string Server::determineResponse(int fd, const HttpRequest& request)
{
    std::string codeStr = "flow_OK";
    std::string keepAlive = request.getHttpHeader("Connection");
    std::string uri = request.getRequestURI();
    
    size_t queryPos = uri.find('?');
    if(queryPos != std::string::npos)
        uri = uri.substr(0, queryPos);

    size_t dotPos = uri.find_last_of('.');
    std::string extension;
    if(dotPos != std::string::npos)
        extension = uri.substr(dotPos);
    
    clientStates[fd].keepAlive = (keepAlive == "keep-alive");
    
    if(clientStates[fd].contentLength > clientStates[fd].serverConfig.maxBodySize)
        return "413";
    if(extension == ".py")
	{
        std::string fullPath = clientStates[fd].serverConfig.rootDirectory + request.getRequestURI();
        clientStates[fd].method = request.getHttpMethod();
        clientStates[fd].body = request.getHttpBody();
        
        if(!HttpResponse::validateRequestMethod(clientStates[fd].method, uri, clientStates[fd].serverConfig))
            return "405";
        else if(request.getHttpMethod() == "GET" || request.getHttpMethod() == "POST")
            return executeCGI(clientStates[fd], fullPath);
        else
            return "405";
    }
    
    return codeStr;
}

void Server::handleClientRequest(int fd)
{
	HttpRequest request(this->clientStates[fd].readBuffer);
    std::string codeStr = determineResponse(fd, request);
    
    if (codeStr.empty())
        return;
    
    HttpResponse response;
    
    if(codeStr == "413")
	{
        std::cout << "WARNING: error code 413... Body is too big" << std::endl;
        response.buildGenericHttpResponse(413, "error code 413");
	}
    else if(codeStr == "405")
        response.buildGenericHttpResponse(405);
    else if(codeStr == "timeout_cgi" || codeStr == "error_cgi_script" || codeStr == "server_error")
        response.buildGenericHttpResponse(500, codeStr);
    else if(codeStr == "flow_OK")
        response.routeRequest(request, this->clientStates[fd]);
    else
        response.buildResponse(200, codeStr, "text/html");
    
    this->clientStates[fd].writeBuffer = response.toHttpString();
    this->clientStates[fd].readBuffer.clear();
    this->clientStates[fd].forked = false;
}

void Server::respondToClient(pollfd &fd)
{
	ClientState &client = clientStates[fd.fd];
	if (client.writeBuffer.empty())
	{
		std::cout << "WARNING: there is no data to send on socket: " << fd.fd << std::endl;
		fd.events = POLLIN;
		return ;
	}
	ssize_t sendBytes = send(fd.fd, client.writeBuffer.c_str(), client.writeBuffer.size(), 0);
	if(sendBytes == 0)
	{
		std::cout << "WARNING: there is no data to send on socket: " << fd.fd << std::endl;
		return ;
	}
	
	if(sendBytes < 0)
	{
		std::cout << "\033[1;31mERROR:\033[0m something went wrong, failed to send response on socket: " << fd.fd << std::endl;
		client.closeConnection = true;
		return ;
	}

	client.writeBuffer.erase(0, sendBytes);
	if (client.writeBuffer.empty())
	{
		client.responding = false;
		fd.events = POLLIN;
		std::cout << "successfull answer on socket: " << fd.fd << std::endl;
		if (!client.keepAlive)
			client.closeConnection = true;
	}
}

std::string readFromPipe(int fd)
{
    std::string ret;
    char buffer[1024];
    int readCount;
    while ((readCount = read(fd, buffer, sizeof(buffer)-1)) > 0)
        ret.append(buffer, readCount);
    return ret;
}

std::string Server::checkCgiStatus(ClientState& client)
{
	int status;
	time_t now;
	time(&now);
	if(difftime(now, client.lastActivity) > client.serverConfig.sendTimeout)
	{
		std::cout << "WARNING: timeout - CGI" << std::endl;
		kill(client.childPid, SIGKILL);
		waitpid(client.childPid, &status, 0);
		close(client.cgiPipe[0]);
		return "timeout_cgi";
	}
	pid_t result = waitpid(client.childPid, &status, WNOHANG);
	if(result == 0) return "";
	if(result == client.childPid)
	{
		if(WIFEXITED(status))
		{
			std::string ret = readFromPipe(client.cgiPipe[0]);
			close(client.cgiPipe[0]);
			return(ret);
		}
		else
		{
			std::cout << "\033[1;31mERROR:\033[0m error while executing CGI" << std::endl;
			close(client.cgiPipe[0]);
			return "error_cgi_script";
		}
	}
	else
	{
		std::cout << "\033[1;31mERROR:\033[0m unexpected return value from waitpid" << std::endl;
		close(client.cgiPipe[0]);
		return "server_error";
	}
}

void Server::setupAndExecChild(ClientState& client, std::string& fullPath) // this function should be restructured!!
{
	char cgiScriptPath[1024] = {0};
	std::string queryData;
	size_t queryStringPos = fullPath.find("?");
	if(queryStringPos != std::string::npos)
	{
		std::strcpy(cgiScriptPath, fullPath.substr(0, queryStringPos).c_str());
		queryData = fullPath.substr(queryStringPos + 1);
	}
	else
		std::strcpy(cgiScriptPath, fullPath.c_str());

	if(client.method == "POST" && queryData.empty())
	{
		queryData = client.body;
	}

	std::string envQuery = "QUERY_STRING=" + queryData;
	std::string envRequestMethod = "REQUEST_METHOD=" + client.method;
	std::ostringstream oss;
	oss << client.contentLength;
	std::string envContentLength = "CONTENT_LENGTH=" + oss.str();
	const char *cgiEnv[] = {envQuery.c_str(), envRequestMethod.c_str(), envContentLength.c_str(), "CONTENT_TYPE=text/html", NULL};

	close(client.cgiPipe[0]);
	dup2(client.cgiPipe[1], STDOUT_FILENO);
	close(client.cgiPipe[1]);
	const char* argv[] = {"/usr/bin/python3", cgiScriptPath, NULL};
	execve(argv[0],  (char* const*)(argv), (char* const*)(cgiEnv));
	std::cout << "\033[1;31mERROR:\033[0m execve failed :(" << std::endl;
	exit(1);
}
