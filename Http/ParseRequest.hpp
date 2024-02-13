/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:04:49 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 13:17:44 by abizyane         ###   ########.fr       */
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

typedef enum {
	RequestLine,
	Headers,
	Body,
	Done,
	Error
} e_parseState;

class ParseRequest {
	private:
		std::string 	_requestBuffer;
		e_parseState	_state;
		std::string 	_method;
		std::string 	_uri;
		std::string 	_version;
		e_statusCode	_status;
		IRequest*		_request;

	public:
		ParseRequest();

		class ErrorException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Error: Invalid request";
				}
		};

		void		parseLine(std::string	request);
		IRequest*	parseRequestLine(std::string&	requestLine); 
		
		~ParseRequest(){};
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