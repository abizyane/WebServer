/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:05:24 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/23 16:47:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Poller.hpp"

Poller::Poller( void ) : std::vector<struct pollfd>() {
}

int	Poller::poll( int timeout )
{
	int ret = ::poll(this->data(), this->size(), timeout);
	return ret;
}

void	Poller::push( int fd, short events )
{
	if (fd > 0) {
		struct pollfd pFd;
		memset(&pFd, 0, sizeof(struct pollfd));
		pFd.fd = fd;
		pFd.events = events;
		this->push_back(pFd);
	}
}

Poller::~Poller( void ) {
}