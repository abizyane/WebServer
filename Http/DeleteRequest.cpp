/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:04:42 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:15 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteRequest.hpp"

DeleteRequest::DeleteRequest(std::string &method, std::string &uri, std::string &version)
    : _method(method), _uri(uri), _version(version){

}

e_statuscode	DeleteRequest::parseRequest(std::__1::string &request){
    (void)request;
    return (HTTP_OK);
}

bool	DeleteRequest::parseHeader(std::__1::string &line){
    (void)line;
    return (true);
}

bool	DeleteRequest::parseBody(std::__1::string &line){
    (void)line;
    return (true);
}

DeleteRequest::~DeleteRequest( void ){

}

