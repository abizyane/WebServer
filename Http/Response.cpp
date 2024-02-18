/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/18 12:51:50 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(IRequest &request): _request(&request), _good(false){
	if (dynamic_cast<GetRequest*>(_request)){
		GetRequest* req = dynamic_cast<GetRequest*>(_request);
		_requestMethod = req->getMethod();
		_requestUri = req->getUri();
		_requestHeaders = req->getHeaders();
		_requestBody = req->getBody();
		_status = req->getParse().getStatusCode();
	}
	else if (dynamic_cast<PostRequest*>(_request)){
		PostRequest* req = dynamic_cast<PostRequest*>(_request);
		_requestMethod = req->getMethod();
		_requestUri = req->getUri();
		_requestHeaders = req->getHeaders();
		_requestBody = req->getBody();
		_status = req->getParse().getStatusCode();
	}
	else{
		DeleteRequest* req = dynamic_cast<DeleteRequest*>(_request);
		_requestMethod = req->getMethod();
		_requestUri = req->getUri();
		_requestHeaders = req->getHeaders();
		_requestBody = req->getBody();
		_status = req->getParse().getStatusCode();
	}
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
	response += "HTTP/1.1 200 OK\r\n";
	response += "Server: Nginx++/1.0.0 (Unix)\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: 0\r\n";
	response += "Connection: close\r\n";
	response += "\r\n";
	_good = true;
	// prapare the response based on the response data
	return response;
}

Response::~Response(){

}