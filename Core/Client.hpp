#pragma once

#include "Selector.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


#define TIMEOUT 10 // in seconds

typedef enum {
	STANDBY, PARSING, DONE
} e_state;


#define SIMPLE_HTTP_RESPONSE "HTTP/1.1 200 OK\r\n"\
                              "Content-Type: text/html\r\n"\
                              "\r\n"\
                              "<html>\r\n"\
                              "<head>\r\n"\
                              "<title>Simple HTTP Response</title>\r\n"\
                              "</head>\r\n"\
                              "<body>\r\n"\
                              "<h1>Hello, World!</h1>\r\n"\
                              "<p>This is a simple HTTP response.</p>\r\n"\
                              "</body>\r\n"\
                              "</html>\r\n"

class	Client
{
	private:
		Selector&		_selector;
		int				sock;
		sockaddr_in		info;
		int				fd[2];
		e_state			state;
		std::string		request;
		std::string		response;
		time_t			_lastActive;
	public:
		Client( Selector& _selector, int sock, sockaddr_in info );
		bool		sendResponse( void );
		~Client( void );
		friend std::ostream&	operator<<( std::ostream& os, const Client& rhs );


	
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

		void	readRequest( char *buffer, int size );
		
	
		inline time_t lastActive( void ) {
			return	_lastActive;
		}
};

