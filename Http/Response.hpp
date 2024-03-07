/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/06 16:53:49 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ProcessRequest.hpp"
#include "../Configuration/MainConf.hpp"
#include "../Configuration/LocationConf.hpp"
#include "DefaultPages.hpp"
#include <sys/stat.h>

typedef enum {
	ERROR,
	RESPONSE,
	BODY,
	DONE
} e_state;

class Response {
	private :
		static std::map<std::string, std::string>   _mimeMap;
		static std::map<e_statusCode, std::string>  _statusMap;
        IRequest*							_request;
		ProcessRequest*						_parse;
		LocationConf*						_location;
		bool								_good;
		e_statusCode						_status;
		e_state								_state;
		size_t								_bodyIndex;
		std::string							_response;
		std::map<std::string, std::string>  _headers;
		std::fstream						_file;
		std::string     					_body;
		
		void								_buildResponse( void );
		void								_processGetResponse( void );
		void								_processPostResponse( void );
		void								_processDeleteResponse( void );
		void								_prepareResponse( void );
		void								_readFile( void );

	public :
		Response(IRequest& request, ProcessRequest& parse, int port);
        static void							initMaps( void );
		bool			good( void );
		bool			sent( void );

		class ResponseException : public std::exception {
			private:
				e_statusCode	__status;

			public:
				ResponseException(e_statusCode status);
				e_statusCode 		getStatus( void );
				virtual const char* what() const throw();
		};

		std::string		GetResponse(size_t lastSent);
    
		~Response();

};

		// std::string& 						GetResponse(void);
		// size_t		 						GetLength(void);
		// std::string& 						GetBody(void);
		// std::string& 						GetContentType(void);
		// e_statusCode 						GetStatusCode(void);
		// std::map<std::string, std::string>& GetHeaders(void);
		// std::string& 						GetHeader(const std::string& key);