/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:45:18 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 11:35:21 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Socket/Socket.hpp"
#include "../Poller/Poller.hpp"
#include "../Client/Client.hpp"
#include "../../Configuration/MainConf.hpp"

#include <map>
#include <vector>

class	Server
{
	private:
		std::vector<Socket*>		_sockets;
		Poller						_poller;
		Poller						_tempPoller;
		std::map<int, Client*>		_clients;
		size_t						nServ;
		
		void	_eraseInactiveClients ( void );
		void	_acceptNewClients( void );
		void	_manageClients( void );
		void	_purgeClient( int idx );
	public:
		Server( void );
		~Server( void );
		void	init( void );
		void	run( void );
};