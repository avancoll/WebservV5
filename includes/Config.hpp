#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "Server.hpp"

class Config {
	public:
		Config(std::string path);
		~Config() {};

		void	printInfo(void);
		void	print_listens(Server server);
		void	print_errors(Server server);
		void	print_locations(Server server);
		void	print_methods_location(std::vector<std::string> method);
		void	print_errors_location(std::map<int, std::string> errors);

		int		check_content() const;

		std::vector<Server>	_servConf;
		std::ifstream		_file;
};

#endif