#include "../includes/Request.hpp"

Request::Request(): _status_line(), _method(), _path(), _protocol() {
}

Request::Request(const std::string& request_string) {
	_status_line = get_first_line(request_string);
	std::vector<std::string> request_line_vector = splitLine(get_first_line(request_string), " ");
	if (request_line_vector.size() != 3) {
		return ;
	}
	_method = request_line_vector[0];
	_path = request_line_vector[1];
	_protocol = request_line_vector[2];
	_body = getHttpRequestBody(request_string);
}

Request&	Request::operator=(const Request& other) {
	if (this == &other) {
		return (*this);
	}
	_status_line = other._status_line;
	_method = other._method;
	_path = other._path;
	_protocol = other._protocol;
	return (*this);
}

void Request::set_header(const std::string& request) {
	std::stringstream ss(request);
	std::string token;
	while (std::getline(ss, token)) {
		if (token == "\r")
			break;
		size_t colon_pos = token.find(':');
		if (colon_pos != std::string::npos) {
			std::string key = token.substr(0, colon_pos);
			std::string value = token.substr(colon_pos + 1);
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);
			_header[key] = value;
		}
	}
	std::string remaining_string((std::istreambuf_iterator<char>(ss)), std::istreambuf_iterator<char>());
	set_body(remaining_string);
}

void	Request::show_data(void) const {
	if (!_path.compare("")) {
		return ;
	}
	std::cout << "\n[REQUEST]" << std::endl;
	if (_method.compare("")) {
		std::cout << "Method: " << _method << std::endl;
	}
	if (_path.compare("")) {
		std::cout << "Path: " << _path << std::endl;
	}
	for (std::map<std::string, std::string>::const_iterator it = _header.begin(); it != _header.end(); it++) {
		if (it->first == "Host" || it->first == "Origin" || it->first == "Content-Type" || it->first == "Content-Length" || it->first == "Connection" || it->first == "Referer")
			std::cout << it->first << ": " << it->second << std::endl;
	}
}
