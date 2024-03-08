#pragma once

#include "Client.hpp"
#include <vector>
#include <fcntl.h>

class	Server {
	friend class CoreServer;
	private:
		int						_sock;
		Selector&				_selector;
		sockaddr_in				_info;
		std::vector<Client*> 	_clients;
	
	public:
		Server (Selector& selector );
		~Server( void );
	
		void	init( const std::string& host, int port );

		inline	int	fileno( void ) const {
			return _sock;
		}
	
		sockaddr_in&	getInfo( void ) {
			return _info;
		}
};