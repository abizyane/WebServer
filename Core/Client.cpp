/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:39:35 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/24 16:22:00 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../utils/utils.hpp"

Client::Client ( Socket* sock ) : sock(sock), joinedTime(getTime()) 
{
}

bool	Client::setRequest( void )
{
	try {
		std::string	data = sock->receive();
		if (data.empty()) return false;
		request.append(data);
		std::cout << "recieved: " << data << '\n';
		joinedTime = getTime();
	} catch( std::exception & e) {
		std::cerr << e.what() << '\n';
		// std::cout << sock->fileno() << '\n';
		// exit(1);
	}
	return true;
}

bool	Client::isAlive( unsigned long maxTime ) const
{
	return (getTime() - joinedTime) < maxTime;
}

void	Client::sendResponse( void )
{
	try {
		sock->send("HTTP/1.1 200 Ok\r\n<h1> siir t9awed </h1>\r\n");
		request = "";
	} catch (std::exception & e ) {
		std::cerr << e.what() << '\n';
	}
}

Socket	*Client::getSock( void )
{
	return sock;
}

bool	Client::responseIsDone( void )
{
	return request.size() > 400;
}

Client::~Client()
{
	delete sock;
}
