/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:46:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:42:04 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseRequest.hpp"

std::string ParseRequest::_method;
std::string ParseRequest::_uri;
std::string ParseRequest::_version;

static std::string	getToken(std::string line) {
		std::string		token;
		size_t			index = line.find_first_of(' ');
		
		token = line.substr(0, index);
		line.erase(0, index);
		line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));

		return token;
}

static int		checkMethod(std::string& method){
	std::string str[11] = {"GET", "POST", "DELETE", "PUT", "HEAD",
		"CONNECT", "OPTIONS", "TRACE", "PATCH", "LINK", "UNLINK"};

	int i = 0;
	for (; i < 11; i++)
		if (str[i] == method)
			break;
	if (i < 3)
		return i;
	if (i < 11)
		return 501;
	return 400;
}

static int	checkUri(std::string& uri){
	std::string allowedChars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-._~:/?#[]@!$&'()*+,;=%");
	
	if (uri[0] != '/' || uri.find_first_not_of(allowedChars) != std::string::npos)
		return 400;
	if (uri.size() > 2083) //replace this with the limit specified in the server_context
		return 414;

	// ...
	return 200;
}

static int	checkVersion(std::string& version){
	if (version.compare(0, 5, "HTTP/"))
		return 400;
	return ((version == "HTTP/1.1")? 200 : 505);
}

IRequest *ParseRequest::parseRequestLine(std::__1::string requestLine){
	IRequest		*Request = NULL;
	try {
		e_statuscode	status = static_cast<e_statuscode>(200);
		_method = getToken(requestLine);	
		_uri = getToken(requestLine);
		_version = getToken(requestLine);

		switch (static_cast<int>(status = static_cast<e_statuscode>(checkMethod(_method)))){
			case 0:
				Request = new GetRequest(_method, _uri, _version);
				break;
			case 1:
				Request = new PostRequest(_method, _uri, _version);
				break;
			case 2:
				Request = new DeleteRequest(_method, _uri, _version);
				break;
			default:
				return NULL; //should return status
		}
		 if ((status = static_cast<e_statuscode>(checkUri(_uri))) != 200 ||
		 	(status = static_cast<e_statuscode>(checkVersion(_version))) != 200)
			return NULL; //should return status
    
	}catch(const std::out_of_range&){
		return NULL;//should return status_code 400 BAD_REQUEST
	}
	return Request;
}

// bool isValidUri(std::string& uri) {
//     std::string reserved = ":/?#[]@!$&'()*+,;=";
//     std::string unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~";

//     for (size_t i = 0; i < uri.size(); ++i) {
//         char c = uri[i];
//         if (reserved.find(c) != std::string::npos || unreserved.find(c) != std::string::npos) {
//             continue;
//         }
//         else if (c == '%' && i + 2 < uri.size() && isxdigit(uri[i + 1]) && isxdigit(uri[i + 2])) {
//             i += 2; // Skip the next two characters
//         }
//         else {
//             return false; // Invalid character
//         }
//     }

//     // Normalize path
//     uri.erase(std::unique(uri.begin(), uri.end(), [](char a, char b) { return a == '/' && b == '/'; }), uri.end());
//     if (uri[uri.size() - 1] != '/') {
//         uri += '/';
//     }

//     return true;
// }