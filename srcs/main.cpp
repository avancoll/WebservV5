#include "Webserv.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Bad file." << std::endl;
		return (1);
	}
	std::string configfile = argv[1];
	std::string	extension = &configfile[configfile.size() - 5];
	if (extension != ".conf") {
		std::cout << "Error: wrong extension format" << std::endl;
		return (1);
	}
	std::ifstream inputfile(configfile);
	if (!inputfile.is_open()) {
		std::cout << "Error: could not open configuration file" << std::endl;
		return (1);
	}
	Config	config(argv[1]);
	if (config.check_content()) {
		return (1);
	}
	Webserv	webserver(config);
	webserver.createServers();
	webserver.runServers();
	return (0);
}