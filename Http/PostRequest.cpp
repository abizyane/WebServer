/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 13:11:28 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostRequest.hpp"

PostRequest::PostRequest(std::string &method, std::string &uri, std::string &version)
    : _method(method), _uri(uri), _version(version){

}

e_statusCode	PostRequest::parseRequest(std::string &request){
    (void)request;
    return (HTTP_OK);
}

bool	PostRequest::_parseHeader(std::string &line){
    (void)line;
    return (true);
}

bool	PostRequest::_parseBody(std::string &line){
    (void)line;
    return (true);
}

PostRequest::~PostRequest( void ){

}

