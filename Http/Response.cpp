/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/11 12:49:04 by abizyane         ###   ########.fr       */
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
		_server = MainConf::getConf()->getServerByHostPort(port, _request->getHeaders()["Host"]);
		if (_server != NULL)
			_location = _server->getUri(_request->getUri());
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
	if (_status >= 400){
		if (_file.is_open())
			_file.close();
		for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
			_headers.erase(it);
		std::srand(time(0));
		std::string tmpName = ".ResponseBody";
		for (int i = 0; i < 20; i++)
			tmpName += to_str(rand());
		_file.open(tmpName,std::ios::out | std::ios::in | std::ios::binary);
		std::string errPage;
		if (_file.is_open()){
			if (_location)
				errPage = _location->getErrPage(static_cast<int>(_status), DefaultPages::getPage(_status));
			else
				errPage = _server->getErrPage(static_cast<int>(_status), DefaultPages::getPage(_status));
			_file.write(errPage.c_str(), errPage.size());
			_headers["Content-Length"] = to_str(errPage.size());
			_headers["Content-Type"] = "text/html";
		}
		else if (_file.fail())
			throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
	}
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
		_response += it->first + ": " + it->second + "\r\n";
	_response += "\r\n";
}

void	Response::_readFile(std::string resource){
	struct stat fileStat;
	_file.open(resource.c_str(), std::ios::in | std::ios::binary | std::ios::out);
	stat(resource.c_str(), &fileStat);
	if (!access(resource.c_str(), F_OK))
		throw Response::ResponseException(HTTP_NOT_FOUND);
	if (fileStat.st_mode & S_IRUSR)
		throw Response::ResponseException(HTTP_FORBIDDEN);
	else if (_file.is_open()){
		size_t size = static_cast<size_t>(fileStat.st_size);
		_headers["Content-Length"] = to_str(size);
		if (S_ISDIR(fileStat.st_mode))
			_headers["Content-Type"] = "Dir";
		else if (_request->getUri().find_last_of('.') != std::string::npos)
			_headers["Content-Type"] = _mimeMap[_request->getUri().substr(_request->getUri().find_last_of('.') + 1)];
		else
			_headers["Content-Type"] = "octet-stream";
		char dt[30];
		strftime(dt, 30, "%a, %d %b %Y %H:%M:%S %Z", gmtime(&fileStat.st_mtime));
		_headers["Last-Modified"] = std::string(dt);
	}
	else
		throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
}

void	Response::_processGetResponse(){
	if (!_location)
		throw Response::ResponseException(HTTP_NOT_FOUND);
	else if (_location->hasRedirect()){
		_headers["Location"] = _location->getRedirectPage().second;
		throw Response::ResponseException(static_cast<e_statusCode>(_location->getRedirectPage().first));	
	}
	if (!_location->methodIsAllowed(_request->getMethod()))
		throw Response::ResponseException(HTTP_METHOD_NOT_ALLOWED);
	std::string resource = _location->getRoot() + _request->getUri();
	_readFile(resource);
	if (_headers["Content-Type"] == "Dir"){
		if (resource[resource.size() - 1] != '/'){
			_headers["Location"] = _request->getUri() + "/";
			throw Response::ResponseException(HTTP_MOVED_PERMANENTLY);
		}
		if (_location->hasIndex()){
			std::vector<std::string>	indexes = _location->getIndex();
			for (size_t i = 0; i < indexes.size(); i++){
				std::string	file = _location->getRoot() + indexes[i];
				if (!access(file.c_str(), F_OK)){
					_readFile(_location->getRoot() + indexes[i]);
					goto HERE;
				}	
			}
		}
		if (_location->dirListingEnabled())
			throw Response::ResponseException(HTTP_FORBIDDEN);
		// resource = _location.getAutoIndex();
		_file.close();
		for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
			_headers.erase(it);
		_readFile(resource);
		return;
	}
	HERE:
	_handleRange();
	// if (_location->hasCgi() && _location->isCgi(_request->getUri().substr(_request->getUri().find_last_of('.') + 1)))
	// 	RUN CGI;
}

void	Response::_writeFile(std::string resource){
	std::string path;
	std::string file(resource);
	struct stat st;
	if (_location->hasUpload()){
		if (resource.find_last_of('/') != std::string::npos){
			path = resource.substr(0, resource.find_last_of('/'));
			resource.erase(0, resource.find_last_of('/') + 1);
			if (resource != "")
				file = resource;
		}
		if (path != "" && stat(path.c_str(), &st) == -1)
				mkdir(path.c_str(), 0777);
		resource = path + "/" + file;
		_file.open(resource,std::ios::in | std::ios::out | std::ios::binary);
		if (_file.is_open()){
			_file.write(_request->getBody().data(), _request->getBody().size());
			_file.close();
		}
		else
			throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
		_headers["Content-Length"] = to_str(_request->getBody().size());
		if (_request->getUri().find_last_of('.') != std::string::npos){
			_headers["Content-Type"] = _mimeMap[_request->getUri().substr(_request->getUri().find_last_of('.') + 1)];
			if (_headers["Content-Type"] == "")
				_headers["Content-Type"] = "octet-stream";	
		}
		else
			_headers["Content-Type"] = "octet-stream";
		char dt[30];
		strftime(dt, 30, "%a, %d %b %Y %H:%M:%S %Z", gmtime(&st.st_mtime));
		_headers["Last-Modified"] = std::string(dt);
		_status = HTTP_CREATED;
		return ;
	}
	_file.open(resource,std::ios::in | std::ios::out | std::ios::binary);
	if (_file.fail())
		throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
	else if (!_file.is_open())
		throw Response::ResponseException(HTTP_NOT_FOUND);
	if (S_ISDIR(st.st_mode))
		_headers["Content-Type"] = "Dir";
}


void	Response::_processPostResponse(){
	if (!_location)
		throw Response::ResponseException(HTTP_NOT_FOUND);
	else if (_location->hasRedirect()){
		_headers["Location"] = _location->getRedirectPage().second;
		throw Response::ResponseException(static_cast<e_statusCode>(_location->getRedirectPage().first));	
	}
	if (!_location->methodIsAllowed(_request->getMethod()))
		throw Response::ResponseException(HTTP_METHOD_NOT_ALLOWED);
	std::string resource = _location->getRoot() + _request->getUri();
	_writeFile(_location->getUploadStore() + _request->getUri());
	if (_status != HTTP_CREATED){
		if (_headers["Content-Type"] == "Dir"){
			_headers.erase("Content-Type");
			if (resource[resource.size() - 1] != '/'){ // redirections
				_headers["Location"] = _request->getUri() + "/";
				throw Response::ResponseException(HTTP_MOVED_PERMANENTLY);
			}
			if (!_location->dirListingEnabled()) // if directory doesn't have index file
				throw Response::ResponseException(HTTP_FORBIDDEN);
		}
		_headers.erase("Content-Type");
		// if (_location->hasCgi() && _location->isCgi(_request->getUri().substr(_request->getUri().find_last_of('.') + 1)))
		// 	RUN CGI;
	}
}

void	Response::_deleteFile(std::string resource){
	struct stat st;
	if (stat(resource.c_str(), &st) == -1)
		throw Response::ResponseException(HTTP_NOT_FOUND);

	if (remove(resource.c_str()) != 0)
		throw Response::ResponseException(HTTP_INTERNAL_SERVER_ERROR);
	else if (!(st.st_mode & S_IRWXU))
		throw Response::ResponseException(HTTP_FORBIDDEN);
	_status = HTTP_NO_CONTENT;
}

void	Response::_processDeleteResponse(){
	std::string resource = _location->getRoot() + _request->getUri();
	_deleteFile(resource);










	
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

