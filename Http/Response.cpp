/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/19 12:32:26 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(IRequest &request): _request(&request), _good(false){
	_requestMethod = _request->getMethod();
	_requestUri = _request->getUri();
	_requestHeaders = _request->getHeaders();
	_requestBody = _request->getBody();
	_status = _request->getParse().getStatusCode();
	_mainConf = MainConf::getConf();
	_prepareResponse();
}

bool    Response::good(){
	return _good;
}

void	Response::_buildResponse(){
	// TODO: prapare the response based on the response data
	// this function now is just for testing
	if (_status == HTTP_OK)
		_response += "HTTP/1.1 200 OK\r\n";
	else
		_response += "HTTP/1.1 404 Not Found\r\n";
	_response += "Server: Nginx++/1.0.0 (Unix)\r\n";
	_response += "Content-Type: text/html\r\n";
	_response += "Content-Length: 0\r\n";
	_response += "Connection: close\r\n";
	_response += "\r\n";
	// if (_status == HTTP_OK)
	// 	response += "<html><body><h1>It works!</h1></body></html>";
	// else
	// 	response += DefaultPages::getPage(HTTP_NOT_FOUND);
}

void	Response::_processGetResponse(){
}

void	Response::_processPostResponse(){
}

void	Response::_processDeleteResponse(){
}

void    Response::_prepareResponse(){
	if (_status == HTTP_OK){
		std::string  methods[3] = {"GET", "POST", "DELETE"};
		for (int i = 0; i < 3; i++)
			if (_requestMethod == methods[i])
				switch (i){
					case 0:
						_processGetResponse();
						break;
					case 1:
						_processPostResponse();
						break;
					default:
						_processDeleteResponse();
				}
	}
	_buildResponse();
	_good = true;
}

std::string    Response::GetResponse(){
	return _response;
}

Response::~Response(){
}