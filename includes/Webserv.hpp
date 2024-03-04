#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "Socket.hpp"
#include "HTTP.hpp"

class Webserv {
	public:
		Webserv(Config& config);
		~Webserv();

		void						printInfo(void);
		void						createServers(void);
		void 						runServers(void);
		void						handleServer(int fd, int filter);
		void						shrink_kqueue_fd(int fd);
		void						handle_client(int fd, size_t serv_index);
		void 						finished_request(int fd, size_t serv_index);
		void 						clear_response(int fd);
		void 						set_write_event(int fd);
		void						close_connection(int fd, Socket *current);
		std::vector<std::string> 	chunk_message(int fd, std::string *message);

	private:
		Config*							_config;
		std::vector<Socket*>			_sockets_list;
		std::map<int, FdInfo> 			_fd_map;
		int 							_kq;
		std::string						_str_req;
		std::string						_str_rep;
		size_t 							_chunk_size;
};

#endif