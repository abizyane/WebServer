/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/07 15:33:15 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

std::map<std::string, std::string> Response::_mimeMap;
std::map<e_statusCode, std::string> Response::_statusMap;

Response::Response(IRequest &request, ProcessRequest& parse, int port): _request(&request), _parse(&parse), _good(false), _state(RESPONSE){
	_bodyIndex = 0;
	_status = _parse->getStatusCode();
	Response::initMaps();
	if (_request != NULL) {
		ServerConf* server = MainConf::getConf()->getServerByPortHost(port, request.getHeaders()["Host"]);
		if (server != NULL)
			_location = server->getUri(_request->getUri());
	}
	std::cout << "port: " << port << std::endl;
	std::cout << "location: " << _location->getRoot() << std::endl;
	_prepareResponse();
}

bool    Response::good(){
	return _good;
}

bool    Response::sent(){
	return _state == DONE;
}

Response::ResponseException::ResponseException(e_statusCode status): __status(status){
}

const char* Response::ResponseException::what() const throw(){
	return _statusMap[__status].c_str();
}

e_statusCode    Response::ResponseException::getStatus( void ){
	return __status;
}

void	Response::_buildResponse(){
	_response += "HTTP/1.1 ";
	_response += _statusMap[_status] + "\r\n";
	{ // the insertion of headers should be done in the _processResponse functions
		_headers["Server"] = "Nginx++/1.0.0 (Unix)";
		// _headers["Content-Type"] = _mimeMap["html"]; // the url instead of "html"
		// _headers["Content-Length"] = ""; // the size of the response body instead of "45"
		_headers["Date"] = "Mon, 04 Mar 2024 18:21:13 GMT"; // the current date instead of "Mon, 04 Mar 2024 18:21:13 GMT"
		// _headers["Accept-Ranges"] = "bytes";
		_headers["Content-Language"] = "en"; // the language of the file instead of "en"
		// _headers["Content-Encoding"] = "gzip"; // the encoding of the file instead of "gzip"
		_headers["Connection"] = "close";
	}
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
		_response += it->first + ": " + it->second + "\r\n";
	_response += "\r\n";

}

void	Response::_readFile(){ // i used "Makefile" as a test file until the getServerbyhostorport() function is implemented
	struct stat fileStat;
	_file.open("index.html", std::ios::in | std::ios::binary | std::ios::out);
	stat("Makefile", &fileStat);
	if (!(fileStat.st_mode & S_IRWXU)) // checks the permissions of the file
		throw Response::ResponseException(HTTP_FORBIDDEN);
	if (_file.is_open()){
		std::stringstream ss;
		ss << fileStat.st_size;
		// _headers["Content-Length"] = ss.str();
		if (_request->getUri().find_last_of('.') != std::string::npos)
			_headers["Content-Type"] = _mimeMap[_request->getUri().substr(_request->getUri().find_last_of('.') + 1)];
		else
			_headers["Content-Type"] = "text/html";
	}
	else
		throw Response::ResponseException(HTTP_NOT_FOUND);
}

void	Response::_processGetResponse(){
	try {
		_readFile();
		
	}
	catch (Response::ResponseException &e){
		_status = e.getStatus();
		_parse->setParseState(Error);
	}
}

void	Response::_processPostResponse(){
	try {
		_readFile();
		
	}
	catch (Response::ResponseException &e){
		_status = e.getStatus();
		_parse->setParseState(Error);
	}
}

void	Response::_processDeleteResponse(){
	try {
		_readFile();
		
	}
	catch (Response::ResponseException &e){
		_status = e.getStatus();
		_parse->setParseState(Error);
	}
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
			index = strtoll(_headers["Content-Length"].c_str(), NULL, 10) - 1;
			_response.erase(0, lastSent);
			if (_response.size() > 0 && _bodyIndex < index)
				response = _response.substr(0, index - _bodyIndex);
			else if (_response.size() == 0 && _file.peek() != std::ifstream::traits_type::eof())
				std::getline(_file, _response, '\0');
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
