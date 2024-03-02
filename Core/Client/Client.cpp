/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:11:04 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/02 14:18:12 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( Socket* sock ) : sockFd(sock), processor(80){ // tatbedel hadi anourdine
}

Client::~Client( void ) {
}

Socket*	Client::sock( void ) const {
	return sockFd;
}

bool	Client::consumStream( void ) {
	try {
		// std::stringstream	ss;
		std::string data = sockFd->receive();
		if (data.empty()) return false;
		processor.parseLine(data);
		// ss << data;
		// streams.push(&ss);
		// std::cout << "recieved: " << data << '\n';
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	}
	return true;
}

void	Client::sendResponse( void ) {
	try {
		if (processor.good())
			_bytesSent = sockFd->send(processor.getResponse()->GetResponse(_bytesSent));
	} catch (std::exception& e){
		std::cerr << e.what() << '\n';
	}
}

bool	Client::ResponseSent( void ){
	return processor.good() && processor.getResponse()->sent();
}
