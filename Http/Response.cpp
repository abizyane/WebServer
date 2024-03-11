/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/11 01:29:39 by nakebli          ###   ########.fr       */
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
		ServerConf* server = MainConf::getConf()->getServerByHostPort(port, _request->getHeaders()["Host"]);
		if (server != NULL)
			_location = server->getUri(_request->getUri());
	}
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

	_headers["Server"] = "Nginx++/1.0.0 (Unix)";
	char dt[30];
	time_t tm = time(0);
	strftime(dt, 30, "%a, %d %b %Y %H:%M:%S %Z", gmtime(&tm));
	_headers["Date"] = std::string(dt);
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
		_response += it->first + ": " + it->second + "\r\n";
	_response += "\r\n";
}

void	Response::_readFile(){
	struct stat fileStat;
	std::string resource = _location->getRoot() + _request->getUri();
	_file.open(resource.c_str(), std::ios::in | std::ios::binary | std::ios::out);
	stat(resource.c_str(), &fileStat);
	if (!(fileStat.st_mode & S_IRWXU))
		throw Response::ResponseException(HTTP_FORBIDDEN);
	if (_file.is_open()){
		size_t size = static_cast<size_t>(fileStat.st_size);
		_headers["Content-Length"] = to_str(size);
		if (_request->getUri().find_last_of('.') != std::string::npos)
			_headers["Content-Type"] = _mimeMap[_request->getUri().substr(_request->getUri().find_last_of('.') + 1)];
		else
			_headers["Content-Type"] = "text/plain";
	}
	else
		throw Response::ResponseException(HTTP_NOT_FOUND);
}

void	Response::_processGetResponse(){
		_readFile();
		_handleRange();
}

void	Response::_processPostResponse(){
		_readFile();
		_handleRange();
}

void	Response::_processDeleteResponse(){
		_readFile();
		_handleRange();
}

void	Response::_handleRange(){
	try {
		if (_request->getHeaders()["Range"] != ""){
			std::string range = _request->getHeaders()["Range"];
			size_t start = strtoll(range.substr(range.find("=") + 1, range.find("-")).c_str(), NULL, 10);
			size_t end = strtoll(range.substr(range.find("-") + 1).c_str(), NULL, 10);
			size_t length = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
			_file.seekg(start, std::ios::beg); // - 1
			_bodyIndex = start;
			if (end > length || start > length || start > end || start < 0 || end < 0)
				throw std::exception();
			_headers["Content-Range"] = "bytes=" + to_str(start) + "-" + to_str(end) + "/" + _headers["Content-Length"];
			// _headers["Content-Length"] = to_str(end - start); // + 1
		}
	}
	catch (std::exception &){
		throw Response::ResponseException(HTTP_REQUESTED_RANGE_NOT_SATISFIABLE);
	}
}

std::string    Response::GetResponse(size_t lastSent){
	std::string		response;
	size_t index;
	switch (_state){
		case RESPONSE:
			response = _response.substr(0, _response.find("\r\n\r\n") + 4);
			_state = BODY;
			_bodyIndex -= response.size();
			break;
		case BODY:
			index = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
			_response.erase(0, lastSent);
			_bodyIndex += lastSent;
			if (_response.size() == 0 && _bodyIndex < index){
				std::vector<char> buffer(index - _bodyIndex);
				_file.read(buffer.data(), index - _bodyIndex);
				std::streamsize readed = _file.gcount();
				_response.assign(buffer.data(), readed);
			}
			if (_response.size() > 0 && _bodyIndex < index){
				response = _response.substr(0, index - _bodyIndex);
			}
			else
				_state = DONE;
			break;
		default:
			break;
    }
	return response;
}

void    Response::_prepareResponse(){
	try{
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
	}
	catch (Response::ResponseException &e){
		_status = e.getStatus();
	}
	_buildResponse();
	_good = true;
}

Response::~Response(){
	if (_file.is_open())
		_file.close();
}

