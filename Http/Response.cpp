/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/23 16:15:42 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(IRequest &request, ProcessRequest& parse): _request(&request), _parse(&parse), _good(false){
	if (_request != NULL){
		_requestMethod = _request->getMethod();
		_requestUri = _request->getUri();
		_requestHeaders = _request->getHeaders();
		_requestBody = _request->getBody();
		_status = _request->getParse().getStatusCode();
	}
	else
		_status = _parse->getStatusCode();
	_mainConf = MainConf::getConf();
	// _serverConf = _mainConf->getServerByHostPort(80, _requestHeaders["Host"]);
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
	else if (_status == HTTP_BAD_REQUEST)
		_response += "HTTP/1.1 400 Bad Request\r\n";
	else if (_status == HTTP_NOT_FOUND)
		_response += "HTTP/1.1 404 Not Found\r\n";
	else if (_status == HTTP_METHOD_NOT_ALLOWED)
		_response += "HTTP/1.1 405 Method Not Allowed\r\n";
	else if (_status == HTTP_INTERNAL_SERVER_ERROR)
		_response += "HTTP/1.1 500 Internal Server Error\r\n";
	else if (_status == HTTP_NOT_IMPLEMENTED)
		_response += "HTTP/1.1 501 Not Implemented\r\n";
	else if (_status == HTTP_SERVICE_UNAVAILABLE)
		_response += "HTTP/1.1 503 Service Unavailable\r\n";
	else if (_status == HTTP_VERSION_NOT_SUPPORTED)
		_response += "HTTP/1.1 505 HTTP Version Not Supported\r\n";
	_response += "Server: Nginx++/1.0.0 (Unix)\r\n";
	_response += "Content-Type: text/html\r\n";
	_response += "Content-Length: 45\r\n";
	_response += "Connection: close\r\n";
	_response += "\r\n";
	// if (_status == HTTP_OK)
	_response += "<html><body><h1>It works!</h1></body></html>";
	// else
		// _response += DefaultPages::getPage(HTTP_NOT_FOUND);
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
					case 2:
						_processDeleteResponse();
					default:
						break;
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