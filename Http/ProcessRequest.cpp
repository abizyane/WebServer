/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:46:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 16:38:49 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ProcessRequest.hpp"

ProcessRequest::ProcessRequest() : _state(RequestLine), _status(HTTP_OK),
	_request(NULL), _response(NULL), _good(false){
}

IRequest*	ProcessRequest::getRequest( void ){
	return _request;
}

Response*	ProcessRequest::getResponse( void ){
	return _response;
}

bool	ProcessRequest::good(){
	return _good;
}

static std::string	getToken(std::string line) {
		std::string		token;
		size_t			index = line.find_first_of(' ');
		
		token = line.substr(0, index);
		line.erase(0, index);
		line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));

		return token;
}

static int		checkMethod(std::string& method){
	std::string str[11] = {"GET", "POST", "DELETE", "PUT", "HEAD",
		"CONNECT", "OPTIONS", "TRACE", "PATCH", "LINK", "UNLINK"};

	int i = 0;
	for (; i < 11; i++)
		if (str[i] == method)
			break;
	if (i < 3)
		return i;
	if (i < 11)
		return 501;
	return 400;
}

static int	checkUri(std::string& uri){
	std::string allowedChars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-._~:/?#[]@!$&'()*+,;=%");
	
	if (uri[0] != '/' || uri.find_first_not_of(allowedChars) != std::string::npos)
		return 400;
	if (uri.size() > 2083) //replace this with the limit specified in the server_context
		return 414;

	// ...
	return 200;
}

static int	checkVersion(std::string& version){
	if (version.compare(0, 5, "HTTP/"))
		return 400;
	return ((version == "HTTP/1.1")? 200 : 505);
}

void ProcessRequest::_generateResponse( void ){
	// ...


	if (_response->good())
		_good = true;
}

void	ProcessRequest::parseLine(std::string	request){
	std::string		line;
	
	_requestBuffer += request;
	while (_requestBuffer.find("\r\n") != std::string::npos || _requestBuffer.find("\n") != std::string::npos){
		_requestBuffer.find("\r\n") != std::string::npos ?
			line = _requestBuffer.substr(0, _requestBuffer.find("\r\n")) :
				line = _requestBuffer.substr(0, _requestBuffer.find("\n"));
		
		_requestBuffer.find("\r\n") != std::string::npos ?
			line.erase(line.find("\r\n")) : line.erase(line.find("\n"));

		if (_state == Headers && line.empty())
			_state = Body;

		switch (_state){
			case RequestLine:
				_parseRequestLine(line);
				break;
			default:
				_status = _request->parseRequest(line);
				break;
			case Error:
			case Done:
				_generateResponse();
		}

		_requestBuffer.find("\r\n") != std::string::npos ?
			_requestBuffer.erase(0, _requestBuffer.find("\r\n")) :
				_requestBuffer.erase(0, _requestBuffer.find("\n"));
	}
}

void	ProcessRequest::_parseRequestLine(std::string &requestLine){
	std::string		method;
	std::string		uri;
	std::string		version;
	
	try {
		method = getToken(requestLine);	
		uri = getToken(requestLine);
		version = getToken(requestLine);

		_status = static_cast<e_statusCode>(checkMethod(method));
		switch (checkMethod(method)){
			case 0:
				_request = new GetRequest(method, uri, version);
				break;
			case 1:
				_request = new PostRequest(method, uri, version);
				break;
			case 2:
				_request = new DeleteRequest(method, uri, version);
				break;
			default:
				_state = Error;
				return;
		}
		if ((_status = static_cast<e_statusCode>(checkUri(uri))) != 200 ||
			(_status = static_cast<e_statusCode>(checkVersion(version))) != 200){
				_state = Error;
				return;
		}
	}catch(const std::out_of_range&){
		_status = HTTP_BAD_REQUEST;		
		_state = Error;
		return;
	}
	_state = Headers;
}

