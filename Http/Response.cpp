/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/10 17:39:13 by abizyane         ###   ########.fr       */
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

void	Response::_writeFile(std::string resource){
	//TODO: upload the body of the request to the server location as a file
	std::string path;
	std::string file(resource);
	struct stat st;
	if (resource.find_last_of('/') != std::string::npos){
		path = resource.substr(0, resource.find_last_of('/'));
		resource.erase(0, resource.find_last_of('/') + 1);
		if (resource != "")
			file = resource;
		else
			throw Response::ResponseException(HTTP_BAD_REQUEST); // should verify this case "POST /path/ "
	}
	if (path != "" && stat(path.c_str(), &st) == -1)
			mkdir(path.c_str(), 0777);
	resource = path + "/" + file;
	_file.open(resource, std::ios::out | std::ios::binary);
	if (_file.is_open()){
		_file.write(_request->getBody().data(), _request->getBody().size());
		_file.close();
	}
	else
		throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
	_status = HTTP_CREATED;
}

void	Response::_deleteFile(std::string resource){
	//TODO: delete the file from the server location
	if (remove(resource.c_str()) != 0)
		throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
}

void	Response::_readFile(std::string resource){
	struct stat fileStat;
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
	std::string resource = _location->getRoot() + _request->getUri();
	
	_readFile(resource);
	_handleRange();
}

void	Response::_processPostResponse(){
	std::string resource = _location->getRoot() + _request->getUri();
	_readFile(resource);
	_handleRange();
}

void	Response::_processDeleteResponse(){
	std::string resource = _location->getRoot() + _request->getUri();
	_readFile(resource);
	_handleRange();
}

void	Response::_handleRange(){
	try {
		if (_request->getHeaders()["Range"] != ""){
			std::string range = _request->getHeaders()["Range"];
			ssize_t length = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
			ssize_t start = strtoll(range.substr(range.find("=") + 1, range.find("-")).c_str(), NULL, 10);
			range.erase(0, range.find("-") + 1);
			ssize_t end = length - 1;
			if (range != "")
				end = strtoll(range.c_str(), NULL, 10);
			_file.seekg(start, std::ios::beg);
			if (end > length || start > length || start > end || start < 0 || end < 0)
				throw Response::ResponseException(HTTP_REQUESTED_RANGE_NOT_SATISFIABLE);
			_headers["Content-Range"] = "bytes " + to_str(start) + "-" + to_str(end) + "/" + _headers["Content-Length"];
			_headers["Content-Length"] = to_str(end - start + 1);
			_status = HTTP_PARTIAL_CONTENT;
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
			// if (!_hasBody)
			// 	_state = DONE;
			_bodyIndex -= response.size();
			break;
		case BODY:
			index = strtoll(_headers["Content-Length"].c_str(), NULL, 10);
			_response.erase(0, lastSent);
			_bodyIndex += lastSent;
			if (_response.size() == 0 && _bodyIndex < index && !_file.eof()){
				std::vector<char> buffer(index - _bodyIndex);
				_file.read(buffer.data(), index - _bodyIndex);
				std::streamsize readed = _file.gcount();
				_response.assign(buffer.data(), readed);
			}
			if (_response.size() > 0 && _bodyIndex < index)
				response = _response.substr(0, index - _bodyIndex);
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

