********************************************************************** */

#ifndef HTTP_HPP
# define HTTP_HPP

#include "Request.hpp"
#include "Response.hpp"
#include "Config.hpp"
#include "CGI.hpp"
#include "utils.hpp"

class HTTP {

	public:
		HTTP(const std::string& request_line, Config* Config, size_t serv_index);
		~HTTP() {};

		Response&	get_response(void) { return _response; };
		void		do_work(void);
		void		build_response(Server& loc_config);
		bool		execute_cgi(void);
		bool		delete_file(void);
		void		redirection(Server& loc_config);
		void		show_request(void);
		void		show_response(void) { _response.show_data(); };
		void		build_directory_listing();
		void		build_directory_listing_down();
		bool		client_close();
		void		find_location(void);
		bool		check_method_allowed(const std::vector<std::string>& loc_methods, const std::vector<std::string>& conf_methods, const std::string& asked_method);
		bool		check_root(const std::string& root);
		bool		check_index(Server& loc, const std::vector<std::string>& conf_index);
		bool		is_index_file(Server& loc, const std::vector<std::string>& conf_index);
		bool		check_max_body(long max_body, const std::string& body);
		bool		check_cgi_extension(const std::string& path);
		bool		check_protocol(void);
	
	private:
		Request			_request;
		Response		_response;
		Server			_config;
		std::string		_location;
		std::string		_req_path;
		std::string		_final_path;
		bool			_failed_request;
};

#endif