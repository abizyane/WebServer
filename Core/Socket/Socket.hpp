/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:18:21 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 11:55:15 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

#define BUFFER_SIZE 1024

typedef int sock_t;

class	Socket
{
	private:
		sock_t		_sockFd;
		sockaddr_in	_addr;

	public:
		Socket( void );
		Socket( int );
		void	open( int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
		void	close( void );
		void	setToNonBlock( void );
		void	bind( const std::string& host, int port );
		void	listen( int backlog = SOMAXCONN );
		sock_t	fileno( void ) const;
		sockaddr_in	getAddr( void ) const;
		Socket*	accept( void );
		std::string	receive( void );
		void		send( const std::string& data );
		// void	connect( )
		// void	setOptions( int level = SOL_SOCKET, int option_name = 1, const void *option_value = (int*)(1), socklen_t option_len = sizeof(int));
	
		~Socket( void );
		// Socket( Socket const& rhs );
		// Socket&	operator=( const Socket& rhs );
};

