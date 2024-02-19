/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/19 11:07:58 by abizyane         ###   ########.fr       */
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
}

bool    Response::good(){
	return _good;
}

void    Response::_prepareResponse(){
	// _response = ...
	_good = true;
}

std::string    Response::GetResponse(){
	std::string  response;
	// this is just for testing
	// TODO: prapare the response based on the response data
	if (_status == HTTP_OK)
		response += "HTTP/1.1 200 OK\r\n";
	else
		response += "HTTP/1.1 404 Not Found\r\n";
	response += "Server: Nginx++/1.0.0 (Unix)\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: 0\r\n";
	response += "Connection: close\r\n";
	response += "\r\n";
	_good = true;
	return response;
}

Response::~Response(){

}