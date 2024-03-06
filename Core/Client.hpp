#pragma once

#include "Selector.hpp"
#include "../Http/ProcessRequest.hpp"
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
		size_t			_bytesSent;

	public:
		Client( Selector& _selector, int sock, sockaddr_in info ) : _selector(_selector), sock(sock), info(info), _processor(info.sin_port){
			_selector.set(sock, Selector::WR_SET | Selector::RD_SET);
			fd[0] = fd[1] = -1;
			_bytesSent = 0;
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

		inline	void	readRequest( char *buffer) {
			_processor.parseLine(buffer);
		}
		
		inline bool		sendResponse( void ) {
			if (_processor.good()){
				std::string response = _processor.getResponse()->GetResponse(_bytesSent);
				_bytesSent = ::send(sock, response.c_str(), response.size(), 0);
				return (_processor.getResponse()->sent());
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
