/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/01 18:59:39 by abizyane         ###   ########.fr       */
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

	// std::map<std::string, std::string>::iterator it = _request->getHeaders().find("Connection");
	// if (it != _request->getHeaders().end() && it->second == "keep-alive"){
	// 	if (_state == BODY){
			
	// 	}
	// 	if (_response != "")
	// 		_state = DONE;
	// }

// 		"Connection: keep-alive\r\n";
// 		"Connection: close\r\n";
std::string    Response::GetResponse(size_t lastSent){
	std::string		response;
	(void)lastSent;
	(void)_state;
	// switch (_state){
	// 	case RESPONSE:
	// 		size_t index;
	// 		_response.find("\r\n\r\n") != std::string::npos ?
	// 			index = _response.find("\r\n\r\n") + 4 : index = _response.find("\n\n") + 2;
	// 		response = _response.substr(0, index);
	// 		_response.erase(0, index);
	// 		_state = BODY;
	// 		break;
	// 	case BODY:
	// 		if (_response.size() > 0){
	// 			response = _response.substr(0, 1024);
	// 			_response.erase(0, 1024);
	// 		}
	// 		else
	// 		_state = DONE;
	// 		break;
	// 	default:
	// 		break;
    // }
	response = _response;
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