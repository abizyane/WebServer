/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:30:35 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/25 18:31:07 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

void    Response::_setCGI_Arguments( void ) {
    std::string requestURI = _request->getUri();
    std::string serverRoot = _location->getRoot();
    _file_path = serverRoot + requestURI;
    _query_string = "";
    _cgi_argv = new char*[2];
    if (requestURI.find('?') != std::string::npos) {
        _query_string = requestURI.substr(requestURI.find('?') + 1);
        _file_path = serverRoot + requestURI.substr(0, requestURI.find('?'));
    }
    _cgi_argv[0] = strdup(normPath(_file_path).c_str());
    _cgi_argv[1] = NULL;
}

void    Response::_initCGI() {
    std::string requestUri = _request->getUri();
    std::string locationRoot = _location->getRoot();
    std::map<std::string, std::string> headers = _request->getHeaders();

	headers["SERVER_PROTOCOL"] = "HTTP/1.1";
	headers["GATEWAY_INTERFACE"] = "CGI/1.1";
	headers["SERVER_SOFTWARE"] = "webserv/1.0";
    headers["REDIRECT_STATUS" ] = "0";
    headers["HTTP_COOKIE"] = headers["Cookie"];
    headers["HTTP_USER_AGENT"] = headers["User-Agent"];
    headers["HTTP_HOST"] = headers["Host"];
    headers["SERVER_PORT"] = to_str(_parse->getPort());
    headers["PATH_INFO"] = _file_path;
    headers["PATH_TRANSLATED"] = _file_path;
    headers["SCRIPT_NAME"] = _file_path;
    headers["REQUEST_URI"] = _file_path;
    headers["DOCUMENT_ROOT"] = locationRoot;
    headers["HTTP_CONNECTION"] = headers["Connection"];
    headers["HTTP_ACCEPT"] = headers["Accept"];
    headers["HTTP_USER-AGENT"] = headers["User-Agent"];
    headers["HTTP_COOKIE"] = headers["Cookie"];
    headers["CONTENT_TYPE"] = headers["Content-Type"];
    headers["REQUEST_METHOD"] = _request->getMethod();
    headers["QUERY_STRING"] = _query_string;
    // ---------------
    std::map<std::string, std::string>::iterator it = headers.begin();
    while (it != headers.end())
    {
        std::string key = it->first;
        if (std::islower(key[1]))
            key = formKey(key);
        setenv(key.c_str(), it->second.c_str(), 1);
        it++;
    }
}

int    Response::_executeCGI( int& fd ) {
    fd = open(_responsefileName.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1) {
		_status = HTTP_INTERNAL_SERVER_ERROR;
		return 1;
	}
	_cgi_pid = fork();
	if (_cgi_pid == -1) {
		_status = HTTP_INTERNAL_SERVER_ERROR;
		return 1;
	}
    if (_cgi_pid == 0) {
        dup2(fd, 1);
		close(fd);
        int fd1 = open(_request->getFileName().c_str(), O_RDONLY, 0666);
		if (fd1 > 0) {
	        dup2(fd1, 0);
        	close(fd1);
		}
        extern char** environ;
		
        execve(_cgi_argv[0], _cgi_argv, environ);
		std::cerr << _cgi_argv[0] << " " <<  strerror(errno) << std::endl;
		exit(502);
    }
    fcntl(fd, F_SETFL, O_NONBLOCK);
    _selector.set(fd, Selector::RD_SET);
	// wait(NULL);
	// _getCGI_Response();
	return 0;
}

void 		Response::_parseCgiHeaders( std::string headers) {
	size_t position = headers.find("\r\n");
	if (headers.empty() || position == std::string::npos){
		_status = HTTP_INTERNAL_SERVER_ERROR;
		return;
	}
	std::string responseLine = headers.substr(0, position);
	size_t pos = responseLine.find(" ");
	int code = atoi(responseLine.substr(pos, 4).c_str());
	if (code < 100 || code > 599)
		_status = HTTP_INTERNAL_SERVER_ERROR;
	else
		_status = static_cast<e_statusCode> (code);
	headers.erase(0, position + 2);
	while (headers.size() > 0){
		position = headers.find("\r\n");
		if (position == std::string::npos || position == 0)
			break;
		std::string header = headers.substr(0, position);
		headers.erase(0, position + 2);
		position = header.find(": ");
		std::string key = header.substr(0, position);
		std::string value = header.substr(position + 2);
		_headers[key] = value;
	}
	if (_headers["Content-Type"] != "text/html")
		_headers["Content-Type"] = "text/html";
}

int Response::_getCGI_Response(void) {
    std::string headers;
    std::string body;
    int status;
    int ret = waitpid(_cgi_pid, &status, WNOHANG);
    if (ret == _cgi_pid) {
        if ((WIFEXITED(status) && WEXITSTATUS(status) != 0) || WIFSIGNALED(status)) {
            _status = HTTP_INTERNAL_SERVER_ERROR;
            goto Here;
        }
        std::ifstream cgiResponse(_responsefileName);
        if (!cgiResponse.is_open()) {
            _status = HTTP_FORBIDDEN;
            goto Here;
        }
        try {
            std::stringstream buffer;
            buffer << cgiResponse.rdbuf();
            cgiResponse.close();
            std::string allfile = buffer.str();

            size_t pos = allfile.find("\r\n\r\n");
            if (pos != std::string::npos) {
                headers = allfile.substr(0, pos + 2);
                body = allfile.substr(pos + 4);
                _parseCgiHeaders(headers);
				_file.close();
				std::remove(_responsefileName.c_str());
				_file.open(_responsefileName.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
                if (!_file.is_open()) {
                    _status = HTTP_INTERNAL_SERVER_ERROR;
                    goto Here;
                }
				_file.write(body.c_str(), body.size());
				_file.close();
				_file.open(_responsefileName.c_str(), std::ios::in | std::ios::out);
            }
        } catch (const std::exception &) {
            _status = HTTP_INTERNAL_SERVER_ERROR;
            goto Here;
        }
    } else {
        return 1;
    }
	Here:
	_buildResponse();
    return 0;
}
