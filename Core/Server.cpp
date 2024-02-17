/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:19:53 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/16 18:15:44 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../utils/utils.hpp"


Server::Server()
{
	MainConf*	conf = MainConf::getConf();
	std::set<unsigned int>	ports = conf->getAllPorts();

	std::set<unsigned int>::iterator	first = ports.begin();
	std::set<unsigned int>::iterator	last = ports.end();

	for ( ; first != last; first++ ) {
		Socket	sock;
		sockaddr_in	addr;
		addr.sin_addr.s_addr = inet_addr("0.0.0.0");
		addr.sin_family = AF_INET;
		addr.sin_port = htons(*first);
		if (sock.bind((sockaddr*)&addr, sizeof(addr)) == false) {
			std::cerr	<< "Error binding socket to port: " << *first
						<< " : " << std::strerror(errno) << '\n';
			continue;
		}
		if (sock.listen() == false) {
			std::cerr	<< "Error listning socket to port: " << *first 
						<< " : " << std::strerror(errno) << '\n';
			continue;
		}
		_sockets.push_back(sock);
		_pollfds.pushFd(sock.getFd());
	}
	// TODO: free befor exit
	if (!_sockets.size())
		exit(0);
}

//	TODO : IMPLEMET 

void	Server::ServerCoreHandle()
{
	while (true)
	{
		if (!_pollfds.poll())
			continue ;
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].events & _pollfds[i].revents)
			{
				if (std::find(_sockets.begin(), _sockets.end(), _pollfds[i].fd) != _sockets.end())
				{
					if ( _pollfds[i].revents & POLLIN ) {
						std::cout << "POLLIN came to me \n";
                    }
				}
				else
				{
					std::cout << "Not a Server Sock \n";
				}
			}
		}
	}
}

// print 

bool	Server::isGood()
{
	return (_sockets.size() != 0);
}

void	Server::printSockets()
{
	std::cout << "Sockets : \n";
	SockIter it = _sockets.begin();
	while (it != _sockets.end())
	{
		std::cout << "socket fd : " << it->getFd() << std::endl;
		it ++;
	}
}

void	Server::printPollfds()
{
	_pollfds.printFds();
}