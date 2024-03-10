/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:04:42 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/10 17:11:30 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteRequest.hpp"

DeleteRequest::DeleteRequest(std::string &method, std::string &uri, ProcessRequest& parse)
	: _method(method), _uri(uri), _version("HTTP/1.1"), _parse(parse){
	_hasBody = false;
	_isChunked = false;
	_contentLength = 0;
	_fileName = ".requestbody";
}

std::string		DeleteRequest::getMethod( void ) const{
	return _method;
}

std::string		DeleteRequest::getUri( void ) const{
	return _uri;
}

std::map<std::string, std::string>	DeleteRequest::getHeaders( void ) const{
	return _headers;
}

std::vector<char>	DeleteRequest::getBody( void ) {
	struct stat	s;
	stat(_fileName.c_str(), &s);

	std::vector<char> buffer(s.st_size);
	_body.open(_fileName.c_str(), std::ios::in);
	_body.read(buffer.data(), s.st_size);
	_body.close();
	return buffer;
}

ProcessRequest&	DeleteRequest::getParse( void ) const{
	return _parse;
}

e_statusCode	DeleteRequest::parseHeader(std::string &line){
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
			return HTTP_BAD_REQUEST; //invalid header
		_headers[key] = value;
	}catch(const std::exception &){
		return HTTP_BAD_REQUEST;
	}
	return HTTP_OK;
}

e_statusCode	DeleteRequest::checkHeaders(void){
	if (_headers.find("Host") == _headers.end())
		return (HTTP_BAD_REQUEST);

	if (_headers.find("Content-Length") != _headers.end() || _headers.find("Transfer-Encoding") != _headers.end()){
		_hasBody = true;
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
		std::srand(std::time(0));
		for (size_t i = 0; i < 20; i++)
			_fileName.push_back(to_str(std::rand())[0]);
		_body.open(_fileName.c_str(), std::ios::out | std::ios::in | std::ios::trunc);
		if (!_body.is_open()){
			_parse.setParseState(Error);
			return HTTP_INTERNAL_SERVER_ERROR;
		}
	}
	else
		_parse.setParseState(Done);
	if (_hasBody)
		_parse.setParseState(Body);
	return HTTP_OK;
}

e_statusCode	DeleteRequest::parseBody(std::string &line){ // TODO: i think that we don't need this function
	std::stringstream ss(line);
	std::string	str;
	size_t	i = 0;
	try{
		if (!_isChunked){
			str = ss.str();
			for (; _bodyIndex + i < _contentLength && i < str.size(); i++);
			_body.write(str.c_str(), i);
			_bodyIndex += i;
			if(_bodyIndex == _contentLength){
				_parse.setParseState(Done);
				_body.close();	
			}
		}
		else{
			std::getline(ss, str, '\n');
			size_t	chunkLen = strtoll(str.c_str(), NULL, 16);
			str.clear();
			str = ss.str();
			for (; _bodyIndex + i < chunkLen && i < str.size(); i++);
			_body.write(str.c_str(), i);
			_bodyIndex += i;
			if (chunkLen == 0){
				_parse.setParseState(Done);
				_body.close();
			}
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

DeleteRequest::~DeleteRequest( void ){
	if (_body.is_open()){
		_body.close();
		std::remove(_fileName.c_str());
	}
}

