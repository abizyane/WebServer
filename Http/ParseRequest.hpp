/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:04:49 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:41:02 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include <algorithm>

#include "IRequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
#include "DeleteRequest.hpp"

class ParseRequest {
    private:
        ParseRequest();
        static std::string  _method;
        static std::string  _uri;
        static std::string  _version;

    public:
        static IRequest*    parseRequestLine(std::string		requestLine); 
};

/*

requestMethod = GET | POST | DELETE

class   RequestFactory:


parseFirstLine();

class   IRequest:
    void    parse( void ) = 0;

class GETRequest extends IRequest:
    void    parse( void ) = 0;

*/