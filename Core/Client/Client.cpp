/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:11:04 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 15:11:43 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( Socket* sock ) : sockFd(sock) {
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
		if (processor.good()) {
			Response* res = processor.getResponse();
			std::cout << res->GetResponse() << '\n';
			sockFd->send(res->GetResponse());
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}