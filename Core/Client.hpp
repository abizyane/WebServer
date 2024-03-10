#pragma once

#include "Selector.hpp"
#include "../Http/ProcessRequest.hpp"
#include "../CGI/Cgi.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>



class	Client
{
	private:
		Selector&		_selector;
		int				sock;
		sockaddr_in		info;
		int				fd[2];
		ProcessRequest	_processor;
		ssize_t			_bytesSent;

	public:
		Client( Selector& _selector, int sock, sockaddr_in info );
		~Client( void );
		bool		sendResponse( void );

		inline int fileno( void ) const {
			return sock;
		}

		inline int writefd( void ) const {
			return fd[0];
		}
		
		inline int readfd( void ) const {
			return fd[1];
		}

		inline	sockaddr_in infos( void ) const {
			return info;
		}

		inline void	readRequest( char *buffer, int size ) {
			_processor.parseLine(buffer, size);
			// Cgi cgi(&_processor, NULL);
			// cgi.init();
			// cgi.execute();
		}

		friend std::ostream&	operator<<( std::ostream& os, const Client& rhs );
};
