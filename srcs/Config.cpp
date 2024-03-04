#include "../includes/Config.hpp"

Config::Config(std::string path) : _servConf(), _file(path) {
	std::string	line;
	std::vector<std::string> split;
	int		status = 0;
	Server*	simple;

	while (getline(_file, line)) {
		if (line.front() == '#')
			continue;
		if (status < 2)
			simple = &_servConf[_servConf.size() - 1];
		if (line.find("server {") != std::string::npos) {
			_servConf.push_back(Server());
			status = 1;
		} else if (line.find("location ") != std::string::npos) {
			split = splitLine(line, " ;\t");
			_servConf[_servConf.size() - 1]._locations.insert(std::make_pair(split[1], Server()));
			status = 2;
			simple = &_servConf[_servConf.size() - 1]._locations[split[1]];
		} else if (line.find("}") != std::string::npos) {
			status--;
		} else if (line.find("listen ") != std::string::npos) {
			split = splitLine(line, " ;\t");
			for (size_t i = 1; i < split.size(); i++) {
				std::vector<std::string> split2;
				split2 = splitLine(split[i], ":");
				if (split2[1].empty()) {
					std::cout << "Bad ip:port format" << std::endl;
					exit(EXIT_FAILURE);
				}
				simple->_listen.insert(std::make_pair(split2[0], split2[1]));
			}
		} else if (line.find("server_name ") != std::string::npos) {
			split = splitLine(line, " ;\t");
			for (size_t i = 1; i < split.size(); i++)
				simple->_serverNames.push_back(split[i]);
		} else if (line.find("error_page ") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_errorPages.insert(std::make_pair(stoi(split[1]), split[2]));
		} else if (line.find("index") != std::string::npos) {
			if (line.find("autoindex") != std::string::npos && line.find("on") != std::string::npos) {
				simple->_autoIndex = true;
			} else if (line.find("autoindex") != std::string::npos) {
				continue;
			} else {
				split = splitLine(line, " ;\t");
				for (size_t i = 1; i < split.size(); i++)
					simple->_index.push_back(split[i]);
			}
		} else if (line.find("root") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_root = split[1];
		} else if (line.find("client_max_body_size") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_maxBody = convertToByte(split[1]);
		} else if (line.find("method") != std::string::npos) {
			split = splitLine(line, " ;\t");
			for (size_t i = 1; i < split.size(); i++)
				simple->_methods.push_back(split[i]);
		} else if (line.find("redirect") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_redirect = split[1];
		} else if (line.find("upload_enable") != std::string::npos && line.find("on") != std::string::npos) {
			simple->_upload = true;
		} else if (line.find("upload_path") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_uploadPath = split[1];
		} else if (line.find("cgi_extension") != std::string::npos) {
			split = splitLine(line, " ;\t");
			for (size_t i = 1; i < split.size(); i++)
				simple->_cgiExt.push_back(split[i]);
		} else if (line.find("cgi_path") != std::string::npos) {
			split = splitLine(line, " ;\t");
			simple->_cgiPath = split[1];
		}
	}
	
}

void	Config::print_listens(Server server) {
	for (std::map<std::string, std::string>::const_iterator it = server._listen.begin(); it != server._listen.end(); ++it) {
		std::cout << "\t|\t" << "Host " << "{" << it->first << "} " << "Port " << "{" << it->second << '}' <<std::endl;
	}
	std::cout << std::endl;
}

void	Config::print_errors(Server server) {
	for (int i = 0; i < 999; i++) {
		if (server._errorPages[i].compare(""))
			std::cout << "\t|\t" << i << " -> " << server._errorPages[i] << std::endl;
	}
}

void	Config::print_methods_location(std::vector<std::string> method) {
	for (size_t i = 0; i < method.size(); i++) {
		if (method[i] == "GET")
			std::cout << "GET ";
		if (method[i] == "POST")
			std::cout << "POST ";
		if (method[i] == "DELETE")
			std::cout << "DELETE ";
	}
	std::cout << std::endl;
}

void	Config::print_errors_location(std::map<int, std::string> errors) {
	int state = 0;
	for (int i = 0; i < 999; i++) {
		if (errors[i].compare(""))
			state = 1;
	}
	if (state) {
		std::cout << "\t|\t|\n\t|\t|\t[Error pages] :" << std::endl;
	} else {
		return ;
	}
	for (int i = 0; i < 999; i++) {
		if (errors[i].compare(""))
			std::cout << "\t|\t|\t|\t" << i << " -> " << errors[i] << std::endl;
	}
}

void	Config::print_locations(Server server) {
	std::map<std::string, Server>	locations = server._locations;
	std::map<std::string, Server>::iterator it;
	for (it = locations.begin(); it != locations.end(); ++it) {
		std::cout << "\t|\t" << "[" << it->first << "] :" << std::endl;
		if (it->second._root.compare(""))
			std::cout << "\t|\t" << "|\t" << "Root : " << it->second._root << std::endl;
		if (it->second._index.size() != 0 && it->second._index[0].compare(""))
			std::cout << "\t|\t" << "|\t" << "Index : " << it->second._index[0] << std::endl;
		if (it->second._redirect.compare(""))
			std::cout << "\t|\t" << "|\t" << "Redirect : " << it->second._redirect << std::endl;
		if (it->second._uploadPath.compare(""))
			std::cout << "\t|\t" << "|\t" << "Upload Path : " << it->second._uploadPath << std::endl;
		if (it->second._cgiPath.compare(""))
			std::cout << "\t|\t" << "|\t" << "CGI Path : " << it->second._cgiPath << std::endl;
		if (!it->second._maxBody)
			std::cout << "\t|\t" << "|\t" << "Client max body size : " << it->second._maxBody << std::endl;
		if (it->second._autoIndex == true)
			std::cout << "\t|\t" << "|\t" << "Autoindex status : on" << std::endl;
		if (it->second._upload == true)
			std::cout << "\t|\t" << "|\t" << "Upload status : on" << std::endl;
		if (it->second._methods.size() != 0) {
			std::cout << "\t|\t" << "|\t" << "Methods : ";
			print_methods_location(it->second._methods);
		}
		print_errors_location(it->second._errorPages);
		std::cout << "\t|\t" << std::endl;
	}
}

void	Config::check_content() const {
	std::vector<int> ports;
	int temp;
	for (size_t i = 0; i < _servConf.size(); i++) {
		for (std::map<std::string, std::string>::const_iterator it = _servConf[i]._listen.begin(); it != _servConf[i]._listen.end(); ++it) {
			std::istringstream(it->second) >> temp;
			ports.push_back(temp);
		}
	}
	for (size_t i = 0; i < ports.size(); i++) {
		for (size_t j = 0; j < ports.size(); j++) {
			if (i == ports.size() - 1 && j == ports.size() - 1)
				break;
			if (i == j)
				j++;
			if (ports[i] == ports[j])
				return (1);
		}
	}
	
}
