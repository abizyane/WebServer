/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:05 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/19 11:03:50 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

class ProcessRequest;

typedef enum{
	HTTP_OK = 200,
	HTTP_CREATED = 201,
	HTTP_NO_CONTENT = 204,
	HTTP_MOVED_PERMANENTLY = 301,
	HTTP_BAD_REQUEST = 400,
	HTTP_FORBIDDEN = 403,
	HTTP_NOT_FOUND = 404,
	HTTP_METHOD_NOT_ALLOWED = 405,
	HTTP_REQUEST_TIMEOUT = 408,
	HTTP_CONFLICT = 409,
	HTTP_REQUEST_ENTITY_TOO_LARGE = 413,
	HTTP_REQUEST_URI_TOO_LONG = 414,
	HTTP_INTERNAL_SERVER_ERROR = 500,
	HTTP_NOT_IMPLEMENTED = 501,
	HTTP_SERVICE_UNAVAILABLE = 503,
	HTTP_VERSION_NOT_SUPPORTED = 505
} e_statusCode;

class IRequest {
	public:
		virtual e_statusCode						checkHeaders( void ) = 0;
		virtual e_statusCode						parseHeader(std::string&	line) = 0;
		virtual e_statusCode						parseBody(std::string&		line) = 0;
		virtual std::string							getMethod( void ) const = 0;
		virtual std::string							getUri( void ) const = 0;
		virtual std::map<std::string, std::string>	getHeaders( void ) const = 0;
		virtual std::string							getBody( void ) const = 0;
		virtual ProcessRequest&						getParse( void ) const = 0;

		virtual ~IRequest(){};
};

#include "ProcessRequest.hpp"