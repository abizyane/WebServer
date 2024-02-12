/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:58:16 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:32 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetRequest.hpp"


GetRequest::GetRequest(std::string &method, std::string &uri, std::string &version)
   : _method(method), _uri(uri), _version(version){

}

e_statuscode	GetRequest::parseRequest(std::__1::string &request){
      (void)request;
    return (HTTP_OK);
}

bool	GetRequest::parseHeader(std::__1::string &line){
   (void)line;
    return (true);
}

bool	GetRequest::parseBody(std::__1::string &line){
   (void)line;
    return (true);
}

GetRequest::~GetRequest( void ){


}