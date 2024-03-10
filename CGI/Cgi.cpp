/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:37:04 by nakebli           #+#    #+#             */
/*   Updated: 2024/03/10 06:55:25 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

//  ========== EXTERNAL FUNCTIONNS ==========
std::string    getFileExtension(std::string request_uri) {
    std::string extension = \
    request_uri.substr(request_uri.find_last_of(".") + 1);
    return extension;
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

//  ========== EXTERNAL FUNCTIONNS ==========

Cgi::Cgi( ProcessRequest* processor, Selector* selector ) 
: _processor(processor), _selector(selector) {
    _cgiRespo_fileName = "/tmp/CGI_" + generateRandomFileName(10);
    _body_file = "/tmp/CGI_" + generateRandomFileName(10);
    (void)_selector; //TODO: remove this later ... 
    setArguments();
}

Cgi::~Cgi( void ) {
    // for (int i = 0; i < 4; i++) {
    //     free (_cgi_argv[i]);
    // }
    // delete _cgi_argv;
}

void    Cgi::setArguments( void ) {
    _cgi_argv = new char*[3];
    std::string extension = \
        getFileExtension(_processor->getRequest()->getUri());
    std::string file_path = \
        _processor->getResponse()->getLocation()->getRoot() + \
        _processor->getRequest()->getUri();
    if (extension == "php") {
// to be changed if the path will be set by the user in the config file 
        _cgi_argv[0] = strdup("/Users/nakebli/Desktop/lastversion/CGI/php-cgi");
    } else if (extension == "py") {
// to be changed if the path will be set by the user in the config file 
        _cgi_argv[0] = strdup("/Users/nakebli/Desktop/lastversion/CGI/python-cgi");
    } else {
        std::cout << "no cgi specified ... " << std::endl;
    }
    _cgi_argv[1] = strdup(file_path.c_str());
    _cgi_argv[2] = NULL;
}

void    Cgi::init() {
    std::map<std::string, std::string> headers = \
        _processor->getRequest()->getHeaders();
    headers["SERVER_PROTOCOL"] = "HTTP/1.1";
	headers["GATEWAY_INTERFACE"] = "CGI/1.1";
	headers["SERVER_SOFTWARE"] = "webserv/1.0";
    headers["REDIRECT_STATUS" ] = "0";
    headers["HTTP_COOKIE"] = headers["Cookie"];
    headers["HTTP_USER_AGENT"] = headers["User-Agent"];
    std::map<std::string, std::string>::iterator it = headers.begin();
    while (it != headers.end())
    {
        std::string key = formKey(it->first);
        setenv(key.c_str(), it->second.c_str(), 1);
        it++;
    }
    // extern char **environ;
    // while (*environ)
    // {
    //     std::cout << *environ << std::endl;
    //     environ++;
    // }
}

void    Cgi::execute( void ) {
    std::ofstream bodyFile(_body_file, std::ios::out | std::ios::trunc);
    if (!bodyFile.is_open()) {
        std::cout << "error 502" << std::endl;
        return ;
    }
    bodyFile << _processor->getRequest()->getBody();
	bodyFile.close();
	int pid = fork();
	if (pid == -1){
        std::cout << "error 500" << std::endl;
		return ;
	}
    if (pid == 0) {
        int fd = open(_cgiRespo_fileName.c_str(), O_CREAT | O_RDWR | O_TRUNC);
        if (fd == -1)
            exit (502);
        if (dup2(1, fd) == -1) {
            close (fd);
            exit (500);
        }
        close(fd);
        int fd1 = open(_body_file.c_str(), O_RDONLY);
        if (fd1 == -1)
            exit(502);
        if (dup2(fd1, 0) == -1){
            close(fd1);
            exit(502);
        }
        close(fd1);
        extern char** environ;
        alarm(5);
        std::cout << _cgi_argv[0] << " - " << _cgi_argv[1] << std::endl;
        execve(_cgi_argv[0], _cgi_argv, environ);
        exit(502);
    }
// ======== TEST ===========  
    // if (wait(NULL) == -1)
    //     std::cerr << "waitError... \n";
    // std::ifstream infile(_cgiRespo_fileName);
    // if (!infile.is_open()) {
    //     std::cerr << "Failed to open the file." << std::endl;
    //     return ;
    // }

    // std::cout << "===========---=========\n";
    
    // std::string line;
    // while (std::getline(infile, line)) {
    //     std::cout << line << std::endl;
    // }
    // std::cout << "===========||=========\n";
    // infile.close();
}

