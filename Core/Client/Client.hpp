/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:11:05 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/25 15:03:47 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <queue>
#include <sstream>
#include "../Socket/Socket.hpp"
#include "../../Http/ProcessRequest.hpp"

class	Client
{
	private:
		Socket*							sockFd;
		ProcessRequest					processor;
		
	public:
		Client( Socket* sock );
		~Client( void );
		Socket*	sock( void ) const;
		bool	consumStream( void );
		void	sendResponse( void );
};