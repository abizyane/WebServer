/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:48:57 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/24 16:53:18 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Socket/Socket.hpp"
#include "../Configuration/MainConf.hpp"
#include "Client.hpp"
#include "Poller/Poller.hpp"
#include <map>
class   Server {
	public :
		Server( void ) {};
		~Server( void ) {};
		void		init();
		void		run();
	private :
		std::map<int, Client*>		_clients;
		std::vector<Socket*>		_listeners;
		Poller						_poller;
		Poller						_tempPoller;
		std::vector<int>			_erasedClients; // erased clients in _poller 
		int							_nServ;

		
		void						_acceptNewClients( void );
		void						_handleClients( void );
		void						_eraseClients( void );
};
