/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/20 08:14:57 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ProcessRequest.hpp"
#include "../Configuration/MainConf.hpp"
#include "../Configuration/LocationConf.hpp"
#include "DefaultPages.hpp"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctime>

 #include <unistd.h>

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

		// added ... CGI
		std::string     					_query_string;
		char**          					_cgi_argv;
		pid_t           					_cgi_pid;
		std::string							_file_path;

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
    
	// added ... CGI
		void            initCGI();
		int				executeCGI( int& fd );
		void			setCGI_Arguments( void );
        int             getCGI_Response( void );
	
		~Response();
};

std::string		getExtension(const std::string &fileName);
