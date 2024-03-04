#include "Server.hpp"

Server::Server():	_listen(),
					_serverNames(),
					_errorPages(),
					_index(),
					_root(),
					_methods(),
					_redirect(),
					_uploadPath(),
					_cgiExt(),
					_cgiPath(),
					_locations() {
	_autoIndex = false;
	_maxBody = -1;
	_upload = false;
}

Server::~Server() {
}
