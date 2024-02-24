/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:34:21 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/24 14:52:14 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket/Socket.hpp"

class Client {
	public :
		Client ( Socket* sock );
		bool	setRequest( void );
		void	sendResponse( void );
		Socket	*getSock( void );
		bool	isAlive( unsigned long maxTime ) const;
		bool	responseIsDone( void );
		~Client();
	private :
		Socket				*sock;
		unsigned long		joinedTime;
		std::string			request;
		std::string			response;
};