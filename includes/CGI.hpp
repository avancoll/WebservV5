#ifndef CGI_HPP
# define CGI_HPP

#include "utils.hpp"

class CGI {
	public:
		CGI(const std::string &cgiDir, const std::string &path, const std::string &requestMetho, const std::string &root);
		~CGI() {};

		void setup_env(const std::map<std::string, std::string> &requestHeaders, const std::string &requestBody);
		void read_program(std::string *response);
		int run_program(const std::map<std::string, std::string> &requestHeaders, const std::string &requestBody, std::string *response);
		std::string &getRoot() { return _root; };

	private:
		std::string			_cgiDir;
		std::string			_command;
		std::string			_path;
		std::string			_query;
		std::string			_requestMethod;

		int					_outpipe[2];
		int					_inpipe[2];
		std::string			_responseBody;
		std::vector<char*>	_envc;
		std::string			_root;
};

#endif