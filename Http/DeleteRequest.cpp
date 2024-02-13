/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:04:42 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 13:10:49 by abizyane         ###   ########.fr       */
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

bool	DeleteRequest::_parseHeader(std::string &line){
    (void)line;
    return (true);
}

bool	DeleteRequest::_parseBody(std::string &line){
    (void)line;
    return (true);
}

DeleteRequest::~DeleteRequest( void ){

}

