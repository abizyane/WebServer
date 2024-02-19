/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:58:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/19 17:35:42 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetRequest.hpp"


GetRequest::GetRequest(std::string &method, std::string &uri, ProcessRequest& parse)
	: _method(method), _uri(uri), _version("HTTP/1.1"), _parse(parse){
	_isChunked = false;
	_contentLength = 0;
	_hasBody = false;
	_bodyIndex = 0;
}

std::string		GetRequest::getMethod( void ) const{
	return _method;
}

std::string		GetRequest::getUri( void ) const{
	return _uri;
}

std::map<std::string, std::string>	GetRequest::getHeaders( void ) const{
	return _headers;
}

std::string		GetRequest::getBody( void ) const{
	return _body;
}

ProcessRequest&	GetRequest::getParse( void ) const{
	return _parse;
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

e_statusCode	GetRequest::parseBody(std::string &line){ // TODO: i think that we don't need this function
	std::stringstream ss(line);
	std::string	str;

	try{
		if (!_isChunked){
			str = ss.str();
			size_t i = _bodyIndex;
			for (; i < _contentLength && i < str.size(); i++)
				_body += str[i];
			_bodyIndex = i;
			if(i == _contentLength)
				_parse.setParseState(Done);
		}
		else{
			std::getline(ss, str, '\n');
			str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
			size_t	chunkLen = strtoll(str.c_str(), NULL, 16);
			str.clear();
			str = ss.str();
			size_t i = _bodyIndex;
			for (; i < chunkLen && i < str.size(); i++)
				_body += str[i];
			_bodyIndex = i;
			if (chunkLen == 0)
				_parse.setParseState(Done);
		}
	}catch(const std::exception &){
		_parse.setParseState(Error);
		return HTTP_BAD_REQUEST;
	}
	line.clear();
    return HTTP_OK;
}

GetRequest::~GetRequest( void ){


}