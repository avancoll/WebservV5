#include "Webserv.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Bad file." << std::endl;
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