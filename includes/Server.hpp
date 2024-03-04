
#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.hpp"

class Server {
	public:
		Server();
		~Server();
		
		std::multimap<std::string, std::string>	_listen;
		std::vector<std::string>				_serverNames;
		std::map<int, std::string>				_errorPages;
		bool									_autoIndex;
		std::vector<std::string>				_index;
		std::string								_root;
		long									_maxBody;
		std::vector<std::string>				_methods;
		std::string								_redirect;
		bool									_upload;
		std::string								_uploadPath;
		std::vector<std::string>				_cgiExt;
		std::string								_cgiPath;
		std::map<std::string, Server>			_locations;
};

#endif