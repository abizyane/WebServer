/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/27 18:17:28 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ProcessRequest.hpp"
#include "../Configuration/MainConf.hpp"
#include "../Configuration/LocationConf.hpp"
#include "DefaultPages.hpp"

typedef enum {
	ERROR,
	RESPONSE,
	BODY,
	DONE
} e_state;

class Response {
	private :
		IRequest*							_request;
		ProcessRequest*						_parse;
		LocationConf*						_location;
		bool								_good;
		e_statusCode						_status;
		e_state								_state;
		size_t								_bodyIndex;
		std::string							_response;
		std::map<std::string, std::string>  _headers;
		std::vector<char>					_body;
		
		void								_buildResponse( void );
		void								_processGetResponse( void );
		void								_processPostResponse( void );
		void								_processDeleteResponse( void );
		void								_prepareResponse( void );
	
	public :
		Response(IRequest& request, ProcessRequest& parse);

		bool			good( void );

		std::string		GetResponse(void);
		~Response();

};

		// std::string& 						GetResponse(void);
		// size_t		 						GetLength(void);
		// std::string& 						GetBody(void);
		// std::string& 						GetContentType(void);
		// e_statusCode 						GetStatusCode(void);
		// std::map<std::string, std::string>& GetHeaders(void);
		// std::string& 						GetHeader(const std::string& key);