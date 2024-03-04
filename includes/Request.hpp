
#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "utils.hpp"

class Request {
	public:
		Request();
		Request(const std::string& status_line);
		~Request() {};

		Request&	operator=(const Request& other);

		const std::string&							get_status_line(void) const { return _status_line; };
		const std::string&							get_method(void) const { return _method; };
		const std::string&							get_path(void) const { return _path; };
		const std::string&							get_protocol(void) const { return _protocol; };
		const std::string&							get_body(void) const { return _body; };
		const std::map<std::string, std::string>&	get_header(void) const { return _header; };

		void										set_status_line(const std::string& status_line) { _status_line = status_line; };
		void										set_method(const std::string& method) { _method = method; };
		void										set_path(const std::string& path) { _path = path; };
		void										set_protocol(const std::string& protocol) { _protocol = protocol; };
		void										set_body(const std::string& str) { _body = str; };
		void										set_header(const std::string& request);

		void										show_data(void) const;

	private:
		std::string							_status_line;
		std::map<std::string, std::string>	_header;
		std::string							_body;
		std::string							_method;
		std::string							_path;
		std::string							_protocol;
};

#endif