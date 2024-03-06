/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:03:18 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 05:09:11 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( Selector& _selector ) : _selector(_selector) {
	memset(&_info, 0, sizeof(sockaddr_in));
}

Server::~Server( void )
{
	close(_sock);
	for (size_t i = 0; i < _clients.size(); i++)  {
		delete _clients[i];
	}
}

void	Server::init( const std::string& host, int port )
{
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