/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/06 11:46:50 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostRequest.hpp"

PostRequest::PostRequest(std::string &method, std::string &uri, ProcessRequest& parse)
    : _method(method), _uri(uri), _version("HTTP/1.1"), _parse(parse){
	_contentLength = 0;
	_bodyIndex = 0;
	_isChunked = false;

	_fileName = ".requestbody";
	// std::srand(time(0));
	// for (size_t i = 0; i < 20; i++)
	// 	_fileName.push_back(std::to_string(std::rand())[0]);
	_body.open(_fileName.c_str(), std::ios::out | std::ios::in | std::ios::trunc);
	if (!_body.is_open())
		_parse.setParseState(Error); //   HTTP_INTERNAL_SERVER_ERROR;
	
}

std::string		PostRequest::getMethod( void ) const{
	return _method;
}

std::string		PostRequest::getUri( void ) const{
	return _uri;
}

std::map<std::string, std::string>	PostRequest::getHeaders( void ) const{
	return _headers;
}

std::string		PostRequest::getBody( void ){
	std::string line;
	_body >> line;
	return line;
}

ProcessRequest&	PostRequest::getParse( void ) const{
	return _parse;
}

e_statusCode	PostRequest::parseHeader(std::string &line){
	try{
		if (line.find(":") == std::string::npos)
			return HTTP_BAD_REQUEST;
		std::string key = line.substr(0, line.find(":"));
		line.erase(0, line.find(":") + 1);
		line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
		line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
		std::string value = line;
		line.clear();
        std::string allowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-!#$%&'*+-.^_|~");
		if (key.empty() || value.empty() || _headers.find(key) != _headers.end() ||
			key.find_first_not_of(allowedChars) != std::string::npos)
			return HTTP_BAD_REQUEST;
		_headers[key] = value;
	}catch(const std::exception &){
		return HTTP_BAD_REQUEST;
	}
	return HTTP_OK;
}

e_statusCode	PostRequest::checkHeaders(void){
	if (_headers.find("Host") == _headers.end())//|| _headers.find("Content-Type") == _headers.end())
		return (HTTP_BAD_REQUEST);
	if (_headers.find("Content-Length") == _headers.end() && _headers.find("Transfer-Encoding") == _headers.end())
		return (HTTP_BAD_REQUEST);
	if (_headers.find("Transfer-Encoding") != _headers.end()){
		if (_headers.find("Transfer-Encoding")->second != "chunked")
			return HTTP_NOT_IMPLEMENTED;
		_isChunked = true;
	}
	if (!_isChunked){
		if (_headers["Content-Length"].find_first_not_of("0123456789") != std::string::npos)
			return HTTP_BAD_REQUEST;
		_contentLength = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
	}
	_parse.setParseState(Body);
	return HTTP_OK;
}

e_statusCode	PostRequest::parseBody(std::string &line){
	std::stringstream ss(line);
	std::string	str;
	size_t	i = 0;
	try{
		if (!_isChunked){
			str = ss.str();
			for (; _bodyIndex + i < _contentLength && i < str.size(); i++)
				_body << str[i];
			_bodyIndex += i;
			if(_bodyIndex == _contentLength)
				_parse.setParseState(Done);
		}
		else{
			std::getline(ss, str, '\n');
			size_t	chunkLen = strtoll(str.c_str(), NULL, 16);
			str.clear();
			str = ss.str();
			for (; _bodyIndex + i < chunkLen && i < str.size(); i++)
				_body << str[i];
			_bodyIndex += i;
			if (chunkLen == 0)
				_parse.setParseState(Done);
			else if (_bodyIndex == chunkLen)
				_bodyIndex = 0;
		}
	}catch(const std::exception &){
		_parse.setParseState(Error);
		return HTTP_BAD_REQUEST;
	}
	line.clear();
	return HTTP_OK;
}

PostRequest::~PostRequest( void ){
	std::remove(_fileName.c_str());
	_body.close();
}
