/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:48:57 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/16 18:14:01 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Configuration/MainConf.hpp"
#include "Socket.hpp"
#include "Poller.hpp"
#include <deque>

class Socket;



typedef std::vector<Socket>::iterator SockIter;

class   Server {
	private :
		std::vector<Socket>     _sockets;
		Poller					_pollfds;

	public :
		Server();
		void	ServerCoreHandle();
		bool	isGood();
		~Server() {};


		// to test
		void	printSockets();
		void	printPollfds();
};
