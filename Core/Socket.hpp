/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:56:36 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/16 17:59:00 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>


class   Socket {
    public:
        Socket( int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0 );
        ~Socket( void );
        bool    bind( const sockaddr *addr, socklen_t addrlen );
        bool    listen( int backlog = SOMAXCONN );
        int     accept( sockaddr *addr, socklen_t *addrlen );
        void    close( void );
        int     getFd( void ) const;
		bool    isgood( void ) const;
        
        bool operator==(int fd) const;
    private:
        int         _fd;
        bool        _good;
};