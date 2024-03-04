#pragma once

#include "Client.hpp"
#include <bits/stdc++.h>
#include <fcntl.h>

class	Server {
	private:
		int						_sock;
		Selector&				_selector;
		sockaddr_in				_info;
	public:
		std::vector<Client*> 	_clients;
		Server (Selector& selector ) : _selector(selector) {
			memset(&_info, 0, sizeof(sockaddr_in));
		};
		
		inline void	init( const std::string& host, int port ) {
			_info.sin_addr.s_addr = inet_addr(host.c_str());
			_info.sin_family = AF_INET;
			_info.sin_port = htons(port);
			_sock = socket(AF_INET, SOCK_STREAM, 0);
			if (_sock == -1)
				throw std::runtime_error("socket() failed");
			if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
				throw std::runtime_error("fcntl() failed");
			if (bind(_sock, (sockaddr*)&_info, sizeof(_info)) == -1)
				throw std::runtime_error("bind() failed");
			if (listen(_sock, SOMAXCONN) == -1)
				throw std::runtime_error("listen() failed");
			int opt = 1;
			if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
				throw std::runtime_error("setsockopt() failed");
			_selector.set(_sock, Selector::RD_SET);
		}

		inline	int	fileno( void ) const {
			return _sock;
		}
		
};