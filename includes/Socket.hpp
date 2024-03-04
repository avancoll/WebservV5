
#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "FdStruct.hpp"
# include "utils.hpp"

class Socket {
	private:
		int					_sockFD;
		sockaddr_in			_address;
		int					_addressLen;
		int					_connection;
		char				_buffer[BUFFER_SIZE];
		std::string 		_request;
		std::vector<int> 	_socket_clients;
		size_t				_serv_index;
	public:
		Socket(int domain, int type, int protocol, int port, u_int32_t interface, size_t serv_index);
		~Socket();
		int	listeningMode(int maxIncoming);
		int	grabConnection(void);
		int	readConnection(int fd, std::string *req);
		int	giveResponse(int fd, std::string message);
		int	giveResponseChunked(int fd, FdInfo*);
		int socketConf(void);
		int	shrink_socket_clients(int to_find);

		std::vector<int>&	get_socket_client(void) { return _socket_clients; };
		size_t	get_serv_index(void) { return _serv_index; };
		int	get_sock_fd(void) { return _sockFD; };


};

#endif