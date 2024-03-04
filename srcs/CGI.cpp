#include "../includes/CGI.hpp"

CGI::CGI(const std::string &cgiDir, const std::string &path, const std::string &requestMethod,  const std::string &root) : _cgiDir(cgiDir), _requestMethod(requestMethod), _root(root) {
	if (_requestMethod == "GET") {
		std::size_t pos = path.find('?');
		std::string rpath = path.substr(0, pos);
		_query = path.substr(pos + 1);
		_command = _cgiDir + rpath;
	} else
		_command = _cgiDir + path;
}

void CGI::setup_env(const std::map<std::string, std::string> &requestHeaders,  const std::string &requestBody) {
	std::vector<std::string> env;
	if (_requestMethod == "GET")
		env.push_back("QUERY_STRING=" + _query);
	env.push_back("PATH_INFO=" + _command);
	env.push_back("REQUEST_METHOD=" + _requestMethod);
	env.push_back("CONTENT_LENGTH=" + std::to_string(requestBody.size()));
	if (_requestMethod == "POST") {
		std::map<std::string, std::string> header = requestHeaders;
		std::string c_type = header["Content-Type"];
		env.push_back("CONTENT_TYPE=" + c_type);
	}
	for (std::map<std::string, std::string>::const_iterator it = requestHeaders.begin(); it != requestHeaders.end(); ++it) {
		std::string envName = "HTTP_" + it->first;
		std::replace(envName.begin(), envName.end(), '-', '_');
		env.push_back(envName + '=' + it->second);
	}
	for (unsigned int i = 0; i < env.size(); ++i)
		_envc.push_back(const_cast<char*>(env[i].c_str()));
	_envc.push_back(nullptr);
}

void CGI::read_program(std::string *response) {
	char buffer[1024];
	while (int bytesRead = read(_outpipe[0], buffer, sizeof(buffer))) {
		if (bytesRead < 0) {
			std::cerr << "Error reading from CGI stdout" << std::endl;
			break;
		}
		response->append(buffer, bytesRead);
	}
}

int CGI::run_program(const std::map<std::string, std::string> &requestHeaders, const std::string &requestBody, std::string *response) {
	char	*arg[3];
	pipe(_outpipe);
	if (_requestMethod == "POST")
		pipe(_inpipe);
	pid_t pid = fork();
	if (pid == 0) {
		setup_env(requestHeaders, requestBody);
		if (_requestMethod == "POST") {
			close(_inpipe[1]);
			dup2(_inpipe[0], 0);
		}
		arg[0] = (char *)"upload.py";
		arg[1] = (char *)getRoot().c_str();
		arg[2] = NULL;
		std::cerr << _command.c_str() << std::endl;
		close(_outpipe[0]);
		dup2(_outpipe[1], STDOUT_FILENO);
		execve(_command.c_str(), arg, _envc.data());
		std::cerr << "Error executing CGI program" << std::endl;
		exit(EXIT_FAILURE);
	} else if (pid > 0) {
		close(_outpipe[1]);
		if (_requestMethod == "POST") {
			close(_inpipe[0]);
			write(_inpipe[1], requestBody.c_str(), requestBody.size());
			close(_inpipe[1]);
		}
		read_program(response);
		close(_outpipe[0]);
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			int exitCode = WEXITSTATUS(status);
			if (exitCode != 0) {
				std::cerr << "CGI program exited with non-zero status: " << exitCode << std::endl;
				return (-1);
			}
		} else {
			std::cerr << "CGI program did not exit normally" << std::endl;
			return (-1);
		}
	} else {
		std::cerr << "Error forking process" << std::endl;
		return (-1);
	}
	return(1);
}