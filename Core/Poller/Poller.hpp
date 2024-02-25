/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:54:46 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/23 16:47:53 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <poll.h>
#include <vector>

class	Poller : public std::vector<struct pollfd> 
{
	public:
		Poller( void );
		int	poll( int timeout = 10 );
		void	push( int fd, short events = POLLIN );
		~Poller( void );
};


