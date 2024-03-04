#include "utils.hpp"

std::vector<std::string>	splitLine(const std::string& line, const std::string& sep) {
	std::vector<std::string>	res;
	std::string					tmp;
	size_t						i = 0;

	while (i < line.length()) {
		if (charInStr(line[i], sep)) {
			if (tmp.length() > 0) {
				res.push_back(tmp);
				tmp.clear();
			}
		} else {
			tmp.append(1, line[i]);
		}
		i++;
	}
	if (tmp.length() > 0)
		res.push_back(tmp);
	return (res);
}

bool	charInStr(const char& c, const std::string& str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (c == str[i])
			return (true);
	}
	return (false);
}

long	convertToByte(std::string& value_str) {
	size_t	multi = 1;
	long		value;
	if (value_str.find_first_not_of("0123456789") != std::string::npos && value_str.find_first_not_of("0123456789") != value_str.size() - 1) {
		return 0;
	} else if (value_str[value_str.size() - 1] != 'M' && value_str[value_str.size() - 1] != 'K' && value_str.find_first_not_of("0123456789") != std::string::npos) {
		return 0;
	} else if (value_str[value_str.size() - 1] == 'K') {
		value_str.erase(value_str.size() - 1, std::string::npos);
		multi = 1024;
	} else if (value_str[value_str.size() - 1] == 'M') {
		value_str.erase(value_str.size() - 1, std::string::npos);
		multi = 1024 * 1024;
	}
	if (value_str.size() > 10) {
		return 0;
	}	
	std::istringstream(value_str) >> value;
	return (value * multi);
}

std::string	get_first_line(const std::string& str) {
	std::string	res;
	size_t	i = 0;
	while (str[i] != '\r' && str[i] != '\n' && i < str.length()) {
		res.append(1, str[i++]);
	}
	return (res);
}

bool file_exists(const std::string& fileName) {
	if (fileName[fileName.size() - 1] == '/')
		return false;
	std::ifstream infile(fileName);
	return infile.good();
}

std::vector<char> readBinaryFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		return std::vector<char>();
	}
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return (buffer);
}

bool is_in_vector(const std::vector<std::string>& vec, const std::string& str) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == str)
			return (true);
	}
	return (false);
}

size_t find_in_str(const std::string& location, const std::string& req_path) {
	size_t	i = 0;
	for (i = 0; i < location.length(); i++) {
		if (location[i] != req_path[i])
			return (0);
	}
	return (i);
}

std::vector<char> str_to_vector(std::string str) {
	std::vector<char> vec(str.begin(), str.end());
	return (vec);
}

std::string getHttpRequestBody(std::string httpRequest) {
	std::size_t bodyStartIndex = httpRequest.find("\r\n\r\n");
	if (bodyStartIndex == std::string::npos) {
		return "";
	}
	return (httpRequest.substr(bodyStartIndex + 4));
}

std::string getHttpRequestWithoutBody(const std::string &httpRequest) {
	size_t bodyStartIndex = httpRequest.find("\r\n\r\n");
	if (bodyStartIndex == std::string::npos) {
		return httpRequest;
	}
	return httpRequest.substr(0, bodyStartIndex);
}
