/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/04 18:30:45 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::map<std::string, std::string> Response::_mimeMap;
std::map<e_statusCode, std::string> Response::_statusMap;

Response::Response(IRequest &request, ProcessRequest& parse, int port): _request(&request), _parse(&parse), _good(false), _state(RESPONSE){
	_bodyIndex = 0;
	_status = _parse->getStatusCode();
	Response::initMaps();
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
	_response += "HTTP/1.1 ";
	_response += _statusMap[_status] + "\r\n";
	{ // the insertion of headers should be done in the _processResponse functions
		_headers["Server"] = "Nginx++/1.0.0 (Unix)";
		_headers["Content-Type"] = _mimeMap["html"]; // the url instead of "html"
		_headers["Content-Length"] = "45"; // the size of the response body instead of "45"
		_headers["Date"] = "Mon, 04 Mar 2024 18:21:13 GMT"; // the current date instead of "Mon, 04 Mar 2024 18:21:13 GMT"
		_headers["Accept-Ranges"] = "bytes";
		_headers["Content-Language"] = "en"; // the language of the file instead of "en"
		_headers["Content-Encoding"] = "gzip"; // the encoding of the file instead of "gzip"
		_headers["Connection"] = "close";
	}
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
		_response += it->first + ": " + it->second + "\r\n";
	_response += "\r\n";

	
	_response += "<html><body><h1>It works!</h1></body></html>"; // the body of the response instead of this
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