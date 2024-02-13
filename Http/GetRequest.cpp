/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:58:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 16:26:15 by abizyane         ###   ########.fr       */
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

bool	GetRequest::_parseHeader(std::string &line){
	(void)line;
	return (true);
}

bool	GetRequest::_parseBody(std::string &line){
	line.clear();
	return (true);
}

GetRequest::~GetRequest( void ){


}