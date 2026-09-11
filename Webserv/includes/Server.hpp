#ifndef SERVER_HPP
#define SERVER_HPP

#include<ctime>
#include<algorithm>
#include<fstream>
#include<streambuf>
#include<cstring>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h> 
#include<vector>
#include<map>
#include<fcntl.h>
#include<poll.h>
#include<errno.h>
#include<netinet/in.h>

#include"HttpRequest.hpp"
#include"utils.hpp"
#include"HttpResponse.hpp"

class Server
{
	private:
		HttpConfig httpConfig;
		std::map<int, ClientState> clientStates; // Maps each client socket file descriptor (fd) to its current state.
		std::map<int, ServerConfig> serverConfigs;
		std::vector<struct pollfd> fds; // Holds all file descriptors monitored by poll()
		std::vector<int> server_fds; // Keeps track of all listening server sockets

		void disconectClient(int fd); 
		bool checkServerFd(int fd);
		ServerConfig& selectServerConfig(std::string &hostName, int port); 
		int acceptClientSocket(int server_fd);
		void handleNewConnection(int server_fd);

		int createSocket(); 
		bool setSocketOptions(int sockfd); 
		bool bindSocket(int sockfd, int port);
		int setupSockets(int port);	
		void parseRequestHeaders(int fd); 
		bool handleInData(int fd); 
		void respondToClient(pollfd &fd); 
		void handleClientRequest(int fd); 
		std::string determineResponse(int fd, const HttpRequest& request);
		void handleCgiOut(std::string str, int fd); 
		std::string executeCGI(ClientState& client, std::string& path); 
		std::string checkCgiStatus(ClientState& client); 
		void setupAndExecChild(ClientState& client, std::string& fullPath); 

	public:
		Server(const HttpConfig& config);
		~Server();
		void initSockets();	
		void handlePollIn(pollfd &fd);
		void handlePollOut(pollfd &fd);
		void handleClientActivity(pollfd &fd, size_t &index);
		void handleEvents(); 
		void launch(); 
};

#endif