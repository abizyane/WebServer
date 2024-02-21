/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:48:57 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/20 17:44:31 by nakebli          ###   ########.fr       */
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
		void			handleListner( pollfd structpoll );
		bool			handleRequest( pollfd structpoll );
		SockIter		findServerSock( int fd );
		bool			isGood();
		~Server() {};

		// to test
		void	printSockets();
		void	printPollfds();
};
