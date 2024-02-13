/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:04:42 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 22:06:04 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteRequest.hpp"

DeleteRequest::DeleteRequest(std::string &method, std::string &uri, std::string &version)
	: _method(method), _uri(uri), _version(version){

}

e_statusCode	DeleteRequest::parseRequest(std::string &request){
	
	(void)request;
	return (HTTP_OK);
}

int     DeleteRequest::_parseHeader(std::string &line){
	try{ 
		if (line.find(":") == std::string::npos)
			return 400;
		std::string key = line.substr(0, line.find(":"));
		key.erase(key.find(":"));
		line.erase(0, line.find(":") + 1);
		if (line.find_first_of(" \t\n\r\f\v") == 0)
			return 400; //value cannot start with a whitespace
		line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
		std::string value = line;
		line.clear();
		std::string allowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-!#$%&'*+-.^_|~");
		if (key.empty() || value.empty() || _headers.find(key) != _headers.end() ||
			key.find_first_not_of(allowedChars) != std::string::npos)
			return 400;
		_headers[key] = value;
	}catch(const std::exception &){
		return 400;
	}
	return 200;
}

int     DeleteRequest::_parseBody(std::string &line){
	(void)line;
	return (true);
}

DeleteRequest::~DeleteRequest( void ){

}

