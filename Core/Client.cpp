/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 06:42:36 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 06:44:36 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( Selector& _selector, int sock, sockaddr_in info ) : _selector(_selector), sock(sock), info(info) {
	_selector.set(sock, Selector::WR_SET | Selector::RD_SET);
	fd[0] = fd[1] = -1;
	state = STANDBY;
	_lastActive = currTime();
}
Client::~Client( void ) {
	_selector.unset(sock, Selector::WR_SET | Selector::RD_SET);
	close(sock);
	close(fd[1]);
	close(fd[0]);
}
void	Client::readRequest( char *buffer, int size ) {
	request.append(buffer, size);
	state = DONE;
	_lastActive = currTime();
}

bool		Client::sendResponse( void ) {
	if (state == DONE) {
		if (::send(sock, SIMPLE_HTTP_RESPONSE, strlen(SIMPLE_HTTP_RESPONSE), 0) < 0) {
			std::cout << strTime() << " send() failed to send response to client " << *this << std::endl;
		} else {
			std::cout << strTime() << " client " << *this << " served " << std::endl;
		}
		return true;
	}
	return false;
}

std::ostream&	operator<<( std::ostream& os, const Client& rhs ) {
	char ip_address[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &(rhs.info.sin_addr), ip_address, INET_ADDRSTRLEN) != NULL) {
		os << ip_address << ":" << ntohs(rhs.info.sin_port);
	} else {
		os << "Failed to convert IP address";
	}
	return os;
}