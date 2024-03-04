#include "Webserv.hpp"

Socket::Socket(int domain, int type, int protocol, int port, u_int32_t interface, size_t serv_index) {
	_sockFD = socket(domain, type, protocol);	
	_connection = -1;
	_addressLen = 0;
	bzero(&_address, sizeof(_address));
	_address.sin_family = domain;
	_address.sin_addr.s_addr = htonl(interface);
	_address.sin_port = htons(port);
	_serv_index = serv_index;
}

Socket::~Socket() {
	std::cout << "Closing Socket" << std::endl;
	if (_connection != -1) {
		close(_connection);
	}
}

int	Socket::listeningMode(int maxIncoming) {
	if ((bind(_sockFD, (struct sockaddr *)&_address, sizeof(_address))) < 0) {
		close(_sockFD);
		return (1);
	}
	if ((listen(_sockFD, maxIncoming)) < 0) {
		close(_sockFD);
		return (1);
	}
}

int	Socket::grabConnection(void) {
	int new_socket = 0;
	struct sockaddr_in cli_addr_tmp;
	socklen_t clilen_tmp = sizeof(cli_addr_tmp);
	while (new_socket != -1) {
		_addressLen = sizeof(_address);
		_connection = accept(_sockFD, (struct sockaddr *)&_address, (socklen_t *)&_addressLen);
		new_socket = _connection;
		if (new_socket < 0) {
			new_socket = -1;
		} else {
			_socket_clients.push_back(new_socket);
		}
	}
	getsockname(_connection, (struct sockaddr *) &cli_addr_tmp, &clilen_tmp);
	return (htons(_address.sin_port));
}

int Socket::readConnection(int fd, std::string *req) {
	int bytesRead;
	_request.clear();
	bzero(_buffer, sizeof(_buffer));
	bytesRead = read(fd, _buffer, BUFFER_SIZE);
	if (bytesRead > 0) {
		for (int i = 0; i < bytesRead; i++)
			_request.push_back(_buffer[i]);
	} else {
		return (bytesRead);
	}
	*req = _request;
	return (bytesRead);
}

int Socket::giveResponse(int fd, std::string message) {
	size_t ret;
	std::cout << "\n[RESPONSE HTML]" << std::endl;
	std::cout << getHttpRequestWithoutBody(message).c_str() << NONE << std::endl << std::endl;
	ret = send(fd, message.c_str(), message.size(), 0);
	return (ret);
}

int Socket::giveResponseChunked(int fd, FdInfo *info) {
	int ret;
	ret = send(fd, info->chunks[info->chunk_sent].data() + info->byte_sent, info->chunks[info->chunk_sent].length() - info->byte_sent, MSG_DONTWAIT);
	return (ret);
}

int	Socket::socketConf() {
	int on = 1;
	int rc;
	rc = fcntl(_sockFD, F_SETFL, O_NONBLOCK);
	if (rc < 0) {
		close(_sockFD);
		std::cerr << "Error setting socket to non-blocking" << std::endl;
		return (1);
	}
	rc = setsockopt(_sockFD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (rc < 0) {
		close(_sockFD);
		std::cerr << "Error setting socket options" << std::endl;
		return (1);
	}
}

int	Socket::shrink_socket_clients(int to_find) {
	for (std::vector<int>::iterator it = _socket_clients.begin(); it != _socket_clients.end(); it++) {
		if (*it == to_find) {
			_socket_clients.erase(it);
			return (1);
		}
	}
}
