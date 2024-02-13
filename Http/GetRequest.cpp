/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:58:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 22:01:44 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetRequest.hpp"


GetRequest::GetRequest(std::string &method, std::string &uri, std::string &version)
	: _method(method), _uri(uri), _version(version){

}

e_statusCode	GetRequest::parseRequest(std::string &request){
	(void)request;
	
	return (HTTP_OK);
}

int		GetRequest::_parseHeader(std::string &line){
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
			return 400; //invalid header
		_headers[key] = value;
	}catch(const std::exception &){
		return 400;
	}
	return 200;
}

int		GetRequest::_parseBody(std::string &line){
	line.clear();
	return (true);
}

GetRequest::~GetRequest( void ){


}