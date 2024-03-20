/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/20 01:50:40 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ProcessRequest.hpp"
#include "../Configuration/MainConf.hpp"
#include "../Configuration/LocationConf.hpp"
#include "DefaultPages.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>

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
		ServerConf*							_server;
		bool								_good;
		e_statusCode						_status;
		e_state								_state;
		ssize_t								_bodyIndex;
		bool								_waitForCgi;

		std::map<std::string, std::string>  _headers;
		std::fstream						_file;
		std::string							_responsefileName;
		std::string							_response;
		Selector&							_selector;
		
		void								_buildResponse( void );
		void								_processGetResponse( void );
		void								_processPostResponse( void );
		void								_processDeleteResponse( void );
		void								_prepareResponse( void );
		void								_readFile(std::string resourse);
		void								_writeFile(std::string resource);
		void								_deleteFile(std::string resource);
		void								_handleRange( void );
		std::string							_autoIndex( const std::string& dirName );
		void								_openFile(std::string &fileName, int param);
		void								_getFileName(std::string &resource);


	public :
		Response(IRequest& request, ProcessRequest& parse, int port, Selector& _selector);
        static void							initMaps( void );
		bool			good( void );
		int				sent( void );

		IRequest*		getRequest( void );

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

std::string		getExtension(const std::string &fileName);
