/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:58:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/16 13:04:24 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetRequest.hpp"


GetRequest::GetRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse)
	: _method(method), _uri(uri), _version(version), _parse(parse){
	_isChunked = false;
	_contentLength = 0;
	_hasBody = false;
}

e_statusCode	GetRequest::checkHeaders(void){
	if (_headers.find("Host") == _headers.end())
		return HTTP_BAD_REQUEST;
	
	if (_headers.find("Content-Length") != _headers.end() || _headers.find("Transfer-Encoding") != _headers.end()){
		_hasBody = true;
		(_headers.find("Transfer-Encoding") != _headers.end()) ? _isChunked = true : _isChunked = false;
		(_isChunked) ? _contentLength = 0 : _contentLength = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
	}
	else
		_parse.setParseState(Done);
	return HTTP_OK;
}

e_statusCode	GetRequest::parseHeader(std::string &line){
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

e_statusCode	GetRequest::parseBody(std::string &line){
	line.clear();
	(void)_parse;
	return (HTTP_OK);
}

GetRequest::~GetRequest( void ){


}