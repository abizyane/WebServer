/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:11:05 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 11:35:06 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Socket/Socket.hpp"

#include <queue>
#include <sstream>

class	Client
{
	private:
		Socket*							sockFd;
		std::queue<std::stringstream*>	streams;
		std::string						response;
	public:
		Client( Socket* sock );
		~Client( void );
		Socket*	sock( void ) const;
		bool	consumStream( void );
		void	sendResponse( void );
};