/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:11:05 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/26 01:37:34 by abizyane         ###   ########.fr       */
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

		bool	ResponseSent( void );
};