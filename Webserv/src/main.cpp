#include"../includes/ConfigHandler.hpp"
#include"../includes/Server.hpp"

int main(int argc, char** argv)
{
	std::cout << "launching webserv..." << std::endl;
	if (argc > 2)
	{
		std::cout << "invalid parameters, use ./webserv OR ./webserv <config-file>" << std::endl;
		return 1;
	}
	ConfigHandler configHandler;
	if (argc == 1)
		configHandler.processConfigFile("config/default.config");
	else
		configHandler.processConfigFile(argv[1]);
	Server bestServer(configHandler.getConfig());
	bestServer.initSockets();
	bestServer.launch();
	return 0;
}
