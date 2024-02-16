/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/16 12:51:55 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostRequest.hpp"

PostRequest::PostRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse)
    : _method(method), _uri(uri), _version(version), _parse(parse){
	_contentLength = 0;
	_isChunked = false;
}

e_statusCode	PostRequest::parseHeader(std::string &line){
	try{
		if (line.find(":") == std::string::npos)
			return HTTP_BAD_REQUEST;
		std::string key = line.substr(0, line.find(":"));
		key.erase(key.find(":"));
		line.erase(0, line.find(":") + 1);
		if (line.find_first_of(" \t\n\r\f\v") == 0)
			return HTTP_BAD_REQUEST; //value cannot start with a whitespace
		line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
		std::string value = line;
		line.clear();
        std::string allowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-!#$%&'*+-.^_|~");
		if (key.empty() || value.empty() || _headers.find(key) != _headers.end() ||
			key.find_first_not_of(allowedChars) != std::string::npos)
			return HTTP_BAD_REQUEST; //invalid header
		_headers[key] = value;
	}catch(const std::exception &){
		return HTTP_BAD_REQUEST;
	}
	return HTTP_OK;
}

e_statusCode	PostRequest::checkHeaders(void){
	if (_headers.find("Host") == _headers.end() || _headers.find("Content-Type") == _headers.end())
		return (HTTP_BAD_REQUEST);
	if (_headers.find("Content-Length") == _headers.end() && _headers.find("Transfer-Encoding") == _headers.end())
		return (HTTP_BAD_REQUEST);
	(_headers.find("Transfer-Encoding") != _headers.end()) ? _isChunked = true : _isChunked = false;
	(_isChunked) ? _contentLength = 0 : _contentLength = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
	return HTTP_OK;
}

e_statusCode	PostRequest::parseBody(std::string &line){
	(void)line;
    return (HTTP_OK);
}

PostRequest::~PostRequest( void ){

}
