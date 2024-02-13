/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 18:05:35 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "IRequest.hpp"
#include <iostream>

class Response {
	private :
		const IRequest*						_request;
		e_statusCode						_status;
		bool								_good;
		std::string							_response;
		std::string							_responsLine;
		std::map<std::string, std::string>  _headers;
		std::string 						_body;
		void								_prepareResponse( void );
	
	public :
		Response(const IRequest& request);

		bool	good( void );
		void	processRequest( void );

		~Response();

};

		// std::string& 						GetResponse(void);
		// size_t		 						GetLength(void);
		// std::string& 						GetBody(void);
		// std::string& 						GetContentType(void);
		// e_statusCode 						GetStatusCode(void);
		// std::map<std::string, std::string>& GetHeaders(void);
		// std::string& 						GetHeader(const std::string& key);