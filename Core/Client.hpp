#pragma once

#include "Selector.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

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
		Selector&	_selector;
		int			sock;
		sockaddr_in	info;
		int			fd[2];
		e_state		state;
		std::string	request;
		std::string	response;
	public:
		Client( Selector& _selector, int sock, sockaddr_in info ) : _selector(_selector), sock(sock), info(info) {
			_selector.set(sock, Selector::WR_SET | Selector::RD_SET);
			fd[0] = fd[1] = -1;
			state = STANDBY;
		}
		
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

		inline	void	readRequest( char *buffer, int size ) {
			request.append(buffer, size);
			state = DONE;
		}
		
		inline bool		sendResponse( void ) {
			if (state == DONE) {
				if (::send(sock, SIMPLE_HTTP_RESPONSE, strlen(SIMPLE_HTTP_RESPONSE), 0) < 0)
					throw std::runtime_error(("send(): failed"));
				return true;
			}
			return false;
		}

		~Client( void ) {
			_selector.unset(sock, Selector::WR_SET | Selector::RD_SET);
			close(sock);
			close(fd[1]);
			close(fd[0]);
		}
};
