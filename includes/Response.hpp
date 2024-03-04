
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "utils.hpp"

class Response {
	public:
		Response();
		Response(const std::string& protocol, size_t status_code, const std::string& status_message);
		~Response() {};

		Response&	operator=(const Response& other);

		std::string								get_status_line(void) const { return _status_line; };
		std::map<std::string, std::string>		get_header(void) const { return _header; };
		std::vector<char>						get_body(void) const { return _body; };
		std::string								get_protocol(void) const { return _protocol; };
		size_t									get_status_code(void) const { return _status_code; };
		std::string								get_status_message(void) const { return _status_message; };

		void			set_status_line(const std::string& protocol, size_t status_code, const std::string& status_message);
		void			set_header(const std::map<std::string, std::string>& header) { _header = header; };
		void			set_body(const std::vector<char>& body);
		void			add_header(const std::string& key, const std::string& value) { _header[key] = value; };
		void			set_content_length(size_t content_length);
		void			set_content_type(const std::string& content_type);
		void			set_protocol(const std::string& protocol);
		void			set_status_code(size_t status_code);
		void			set_status_message(const std::string& status_message);
		void			show_status_line(void) const;
		void			show_header(void) const;
		void			show_body(void) const;
		void			show_data(void) const;
		void			build_response(const std::string& path);
		std::string		give_response(void);
		void			update_status_line(void);
		void			update_header(void);

	private:
		std::string							_status_line;
		std::map<std::string, std::string>	_header;
		std::vector<char>					_body;

		std::string		_protocol;
		size_t			_status_code;
		std::string		_status_message;
		size_t			_content_length;
		std::string		_content_type;
};

#endif