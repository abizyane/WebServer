#pragma once

#include "Server.hpp"
#include "../Configuration/MainConf.hpp"

#define BUFFER_SIZE 1024

#define HOST "127.0.0.1"


class	CoreServer
{
	private:
		std::vector<Server*>	_servers;
		Selector				_selector;

		int		_nfds( void );
		void	_acceptNewClient( Server* server );
		void	_manageClients( Server* server );
		void	_purgeClient( Server* server, std::vector<Client*>::iterator& it );

		CoreServer( void );

		static CoreServer*	_instance;
	public:
		static CoreServer*	getCore( void );
		~CoreServer( void );
		void	init( void );
		void	run( void );
};