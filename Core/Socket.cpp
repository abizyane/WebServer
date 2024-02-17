/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:00:18 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/16 18:07:13 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket ( int domain, int type, int protocol)
{
	_fd = socket( domain, type, protocol );
	if ( _fd < 0 ) {
		std::cerr << "error creating socket: " << std::strerror(errno) << std::endl;
		_good = false;
	}
	fcntl( _fd, F_SETFL, O_NONBLOCK);
}

bool	Socket::bind( const sockaddr *addr, socklen_t addrlen )
{
	if ( ::bind( _fd, addr, addrlen ) < 0 )
		return false;
	return true;
}

bool	Socket::listen( int backlog )
{
	if ( ::listen( _fd, backlog ) < 0 )
		return false;
	return true;
}

int		Socket::accept( sockaddr *addr, socklen_t *addrlen )
{
	int fd = ::accept( _fd, addr, addrlen );
	if (fd < 0)
		std::cerr << "error accepting socket: " << std::strerror(errno) << std::endl;
	return fd;
}

void	Socket::close( void )
{
	if ( _good )
		::close( _fd );
}

int		Socket::getFd( void ) const
{
	return (_fd);
}

bool	Socket::isgood( void ) const
{
	return (_good);
}

bool Socket::operator==(int fd) const
{
	return this->_fd == fd;
}

Socket::~Socket( void ) {}
