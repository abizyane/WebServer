/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:48 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 18:06:23 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(const IRequest &request): _request(&request), _status(HTTP_OK), _good(false){
    (void)_request;
    (void)_status;
}

bool    Response::good(){
    return _good;
}

void    Response::_prepareResponse(){
    // _response = ...
    _good = true;
}

void    Response::processRequest( void ){
    
}

Response::~Response(){

}