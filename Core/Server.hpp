/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:48:57 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/19 14:15:35 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Configuration/MainConf.hpp"
#include "Socket.hpp"
#include "Poller.hpp"
#include "Client.hpp"
#include "../Http/Response.hpp"
#include "../utils/utils.hpp"
#include <deque>

class Socket;

typedef std::vector<Socket>::iterator 		SockIter;
typedef std::vector<ClientInfo*>::iterator 	ClientIter;

class   Server {
	private :
		std::vector<Socket>     			_sockets;
		std::vector<ClientInfo*>			_clients;
		Poller								_pollfds;

	public :
		Server();
		ClientIter		findClient( int	fd );
		void			ServerCoreHandle( void );
		void			handleListner( int fd );
		bool			handleRequest( int i );
		SockIter		findServerSock( int i );
		bool			isGood();
		~Server() {};

		// to test
		void	printSockets();
		void	printPollfds();
};
