/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:35:24 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 10:13:26 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(void) : _sockFd(-1)
{
}

Socket::Socket( int sock ) : _sockFd(sock) {
	
}
void Socket::open(int domain, int type, int protocol)
{
	_sockFd = ::socket(domain, type, protocol);
	if (_sockFd < 0)
		throw std::runtime_error("error creatin new socket: " + std::string(strerror(errno)));
}

void Socket::close(void)
{
	::close(_sockFd);
	_sockFd = -1;
}

void Socket::setToNonBlock( void )
{
	int flags = fcntl(_sockFd, F_GETFL, 0);
	if (flags < 0)
		throw std::runtime_error("error getting socket flags: " + std::string(strerror(errno)));
	if (fcntl(_sockFd, F_SETFL, flags | O_NONBLOCK) < 0)
		throw std::runtime_error("error set socket to non blocking : " + std::string(strerror(errno)));
}

void Socket::bind(const std::string &host, int port)
{
	_addr.sin_addr.s_addr = inet_addr(host.c_str());
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	if (::bind(_sockFd, (sockaddr*)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("error binding socket to : " + host + ":" + std::to_string(port)); // TODO: remove to_string
	int opt = 1;
	if (setsockopt(_sockFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("error set socket options : " + host + ":" + std::to_string(port)); // TODO: remove to_string
		
}

void Socket::listen(int backlog )
{
	if (::listen(_sockFd, backlog) < 0)
		throw std::runtime_error("error listening for new connections: " + std::string(strerror(errno)));
}

Socket *Socket::accept( void )
{
	Socket*	client = new Socket();
	socklen_t len = 0;
	client->_sockFd = ::accept(_sockFd, (sockaddr*)&_addr, &len);
	if (client->_sockFd < 0) {
		delete client;
		throw std::runtime_error("error accepting new connetion: " + std::string(strerror(errno)));
	}
	return client;
}

std::string	Socket::receive( void )
{
	char	buffer[BUFFER_SIZE] = {0};
	std::string	data;
	int ret = ::recv(_sockFd, buffer, BUFFER_SIZE, 0);
	if (ret == -1)
		throw std::runtime_error("faild reading from socket: " + std::string(strerror(errno)));
	// if (ret == 0)
	// 	return data;
	data.append(buffer, ret);
	return data;
}

void		Socket::send( const std::string& data )
{
	if (::send(_sockFd, data.c_str(), data.size(), 0) < 0)
		throw std::runtime_error("faild to send data in socket: " + std::string(strerror(errno)));
}

sock_t	Socket::fileno( void ) const
{
	return _sockFd;
}

sockaddr_in	Socket::getAddr( void ) const
{
	return _addr;
}

Socket::~Socket(void)
{
	close();
}
