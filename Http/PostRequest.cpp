/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:49 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostRequest.hpp"

PostRequest::PostRequest(std::string &method, std::string &uri, std::string &version)
    : _method(method), _uri(uri), _version(version){

}

e_statuscode	PostRequest::parseRequest(std::__1::string &request){
    (void)request;
    return (HTTP_OK);
}

bool	PostRequest::parseHeader(std::__1::string &line){
    (void)line;
    return (true);
}

bool	PostRequest::parseBody(std::__1::string &line){
    (void)line;
    return (true);
}

PostRequest::~PostRequest( void ){

}

