/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/04 14:19:38 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(IRequest &request, ProcessRequest& parse, int port): _request(&request), _parse(&parse), _good(false), _state(RESPONSE){
	_bodyIndex = 0;
	_status = _parse->getStatusCode();
	(void)port;
	if (_request != NULL)
		_location = MainConf::getConf()->getServersConf()[0]->getUri(_request->getUri()); // bdel hadi b getServerbyhostorport()
	_prepareResponse();
}

bool    Response::good(){
	return _good;
}

bool    Response::sent(){
	return _state == DONE;
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

std::string    Response::GetResponse(size_t lastSent){
	std::string		response;
	size_t index;
	switch (_state){
		case RESPONSE:
			_response.find("\r\n\r\n") != std::string::npos ?
				index = _response.find("\r\n\r\n") + 4 : index = _response.find("\n\n") + 2;
			response = _response.substr(0, index);
			_state = BODY;
			break;
		case BODY:
			index = 45; // 45 is just for testing => [ strtoll(_headers["Content-Length"].c_str(), NULL, 10) - 1 ]
			_response.erase(0, lastSent);
			if (_response.size() > 0 && _bodyIndex < index)
				response = _response.substr(0, index - _bodyIndex);
			else
				_state = DONE; 
			_bodyIndex += lastSent;
			break;
		default:
			break;
    }
	return response;
}

void    Response::_prepareResponse(){
	if (_status == HTTP_OK){
		std::string  methods[3] = {"GET", "POST", "DELETE"};
		for (int i = 0; i < 3; i++)
			if (_request->getMethod() == methods[i])
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

Response::~Response(){
}