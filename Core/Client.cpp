/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:39:35 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/17 20:38:26 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


ClientInfo&	ClientInfo::operator=( const ClientInfo& rhs ) {
	this->addr = rhs.addr;
	this->len = rhs.len;
	this->fd = rhs.fd;
	return *this;
}

ClientInfo::ClientInfo( const ClientInfo& rhs ) {
	this->addr = rhs.addr;
	this->len = rhs.len;
	this->fd = rhs.fd;
};

ClientInfo::ClientInfo( int sockfd ) {
	len = sizeof(addr);
	good = true;
	fd = accept(sockfd, (struct sockaddr *)&addr, &len);
	if (fd < 0)
		std::cerr << "failed to accept new client" << std::endl;
	else
		std::cerr << "new client connected" << std::endl;
}

ClientInfo::~ClientInfo( void ) {
    close(fd);
}
