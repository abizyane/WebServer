/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:37:04 by nakebli           #+#    #+#             */
/*   Updated: 2024/03/15 06:54:05 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"
// /usr/bin/perl
//  ========== EXTERNAL FUNCTIONNS ==========
std::string    getFileExtension(std::string request_uri) {
    std::string extension = \
    request_uri.substr(request_uri.find_last_of(".") + 1);
    extension = extension.substr(0, extension.find('?'));
    return extension;
}

void    Cgi::printfile() {
    std::fstream infile(_cgiRespo_fileName);
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file....." << std::endl;
        return ;
    }

    std::cout << "===========---=========\n";

    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }

    std::cout << "===========||=========\n";

    infile.close();
}

std::string generateRandomFileName(int length) {
    const std::string allowed_chars = \
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::string file_name = "CGI_";
    std::srand(std::time(0));

    for (int i = 0; i < length; ++i) {
        int index = std::rand() % allowed_chars.size();
        file_name += allowed_chars[index];
    }

    return file_name;
}

std::string formKey(std::string key)
{
    std::string formedKey = key;
    for (size_t i = 0; i < formedKey.size(); i++)
    {
        if (formedKey[i] == '-')
            formedKey[i] = '_';
        else
            formedKey[i] = toupper(formedKey[i]);
    }
    return formedKey;
}

//  ========== INTERNAL FUNCTIONNS ==========

Cgi::Cgi( ProcessRequest* processor, Selector* selector ) 
: _processor(processor), _selector(selector) {
    _cgiRespo_fileName = "/tmp/CGI_" + generateRandomFileName(10) + ".html";
    _body_file = "/tmp/CGI_" + generateRandomFileName(10);
    (void)_selector;
    setArguments();
}

Cgi::~Cgi( void ) {
    for (int i = 0; i < 4; i++) {
        free (_cgi_argv[i]);
    }
    delete _cgi_argv;
}

void    Cgi::setArguments( void ) {
    std::string requestURI = _processor->getRequest()->getUri();
    std::string serverRoot = _processor->getResponse()->getLocation()->getRoot();
    _file_path = serverRoot + requestURI;
    _query_string = "";
    _cgi_argv = new char*[3];
    if (requestURI.find('?') != std::string::npos) {
        _query_string = requestURI.substr(requestURI.find('?') + 1);
        _file_path = serverRoot + requestURI.substr(0, requestURI.find('?'));
    }
    std::string extension = getFileExtension(requestURI);
    if (extension == "php") {
// to be changed if the path will be set by the user in the config file
        _cgi_argv[0] = strdup("/Users/nakebli/Desktop/lastversion/CGI/php-cgi");
    } else if (extension == "py") {
// to be changed if the path will be set by the user in the config file
        _cgi_argv[0] = strdup("/Users/nakebli/Desktop/lastversion/CGI/python-cgi");
    } else {
        std::cout << "no cgi specified ... " << std::endl;
    }
    _cgi_argv[1] = strdup(_file_path.c_str());
    _cgi_argv[2] = NULL;
}

void    Cgi::init() {
    std::string requestUri = _processor->getRequest()->getUri();
    std::string locationRoot = \
        _processor->getResponse()->getLocation()->getRoot();
    std::map<std::string, std::string> requestheaders = \
        _processor->getRequest()->getHeaders();
    std::map<std::string, std::string> headers = \
        requestheaders;
    headers["SERVER_PROTOCOL"] = "HTTP/1.1";
	headers["GATEWAY_INTERFACE"] = "CGI/1.1";
	headers["SERVER_SOFTWARE"] = "webserv/1.0";
    headers["REDIRECT_STATUS" ] = "0";
    headers["HTTP_COOKIE"] = headers["Cookie"];
    headers["HTTP_USER_AGENT"] = headers["User-Agent"];
    //-----new----
    headers["HTTP_HOST"] = requestheaders["Host"];
    headers["SERVER_PORT"] = to_str(htons(_processor->getInfo().sin_port));
    headers["PATH_INFO"] = _file_path;
    headers["PATH_TRANSLATED"] = _file_path;
    headers["SCRIPT_NAME"] = _file_path;
    headers["REQUEST_URI"] = _file_path;
    headers["DOCUMENT_ROOT"] = locationRoot;
    headers["HTTP_CONNECTION"] = requestheaders["Connection"];
    // headers["SERVER_NAME"] = response.getServer().getServerName();
    headers["HTTP_ACCEPT"] = requestheaders["Accept"];
    headers["HTTP_USER-AGENT"] = requestheaders["User-Agent"];
    headers["HTTP_COOKIE"] = requestheaders["Cookie"];
    headers["CONTENT_TYPE"] = requestheaders["Content-Type"];
    headers["REQUEST_METHOD"] = _processor->getRequest()->getMethod();
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
    // extern char** environ;
    // int j = 0;
    // while (environ[j])
    //     std::cout << environ[j++] << std::endl;
    // exit(1);
}

void    Cgi::execute( int& fd ) {
    std::ofstream bodyFile(_body_file, std::ios::out | std::ios::trunc);
    if (!bodyFile.is_open()) {
        std::cout << "error 502" << std::endl;
        return ;
    }
    bodyFile << _processor->getRequest()->getBody();
	bodyFile.close();
    fd = open(_cgiRespo_fileName.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1)
        return ;
	pid = fork();
	if (pid == -1){
        std::cout << "error 500" << std::endl;
		return ;
	}
    if (pid == 0) {
        dup2(fd, 1);
        close(fd);
        int fd1 = open(_body_file.c_str(), O_RDONLY); // check if request has body
        if (fd1 == -1)
            exit(502);
        if (dup2(fd1, 0) == -1) {
            close(fd1);
            exit(502);
        }
        close(fd1);
        extern char** environ;
        execve(_cgi_argv[0], _cgi_argv, environ);
        exit(502);
    }
    // fcntl(fd, F_SETFL, O_NONBLOCK);
    // _selector->set(fd, Selector::RD_SET);
    // ======== TEST ===========
    wait(NULL);
    addHeaders();
    printfile();
}

int    Cgi::addHeaders( void ) {
    std::string     headers;
    std::string     body;
    int             status;
    int ret = waitpid(pid, &status, WNOHANG);
    if (ret != 0 && ret != -1) {
        if (WEXITSTATUS(status) != 0)
            return (502);
        std::cout << "entered2\n";
        std::ifstream cgiResponse(_cgiRespo_fileName);
        if (!cgiResponse.is_open())
            return (502);
        std::stringstream buffer;
        buffer << cgiResponse.rdbuf();
        cgiResponse.close();
        std::string allfile = buffer.str();
        size_t pos = allfile.find("\r\n\r\n");
        if (pos != std::string::npos) {
            headers = allfile.substr(0, pos + 2);
            body = allfile.substr(pos + 4);
        }
        headers = "HTTP/1.1 200 OK\r\n" + headers \
        + "Content-Lenght: " + to_str(body.size()) + "\r\n\r\n";
        body = headers + body;
        std::ofstream outputFile(_cgiRespo_fileName.c_str(), std::ios::out | std::ios::trunc);
        if (!outputFile)
            return (502);
        outputFile << body;
        outputFile.close();
        return 0;
    }
    return 1;
}
