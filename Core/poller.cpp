/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poller.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:15 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/15 14:35:45 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Poller.hpp"

Poller::Poller( void ) {
}


Poller::~Poller( void ) {
}

void	Poller::pushFd( int fd, short events ) {
	
struct pollfd	newFd;
	newFd.fd = fd;
	newFd.revents = 0;
	newFd.events = events;
	__pollfds.push_back(newFd);
}

struct FdEquals {
	int	targetFd;
	FdEquals(int fd) : targetFd(fd) {}
	bool operator()(const struct pollfd& pfd) const {
		return pfd.fd == targetFd;
	}
};

void Poller::erase(int fd) {
    
    __pollfds.erase(std::remove_if(__pollfds.begin(), __pollfds.end(),
		FdEquals(fd)), __pollfds.end());
}

bool	Poller::poll( int timeout ) {		
	int	readySocket = ::poll( __pollfds.data(), __pollfds.size(), timeout );
	if ( readySocket < 0 ) {
		std::cerr << "Error in poll: " << strerror(errno) << std::endl;
		return false;
	}
	return readySocket != 0;
}

struct pollfd& Poller::operator[]( const int& idx ) {
	return __pollfds.at(idx);
};

size_t Poller::size( void ) const {
	return __pollfds.size();
};
