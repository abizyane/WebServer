/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:34:21 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/20 20:13:50 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Configuration/MainConf.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include "../Http/ProcessRequest.hpp"

class	ClientInfo {
	public :
		sockaddr_in		addr;
		socklen_t		len;
		int				fd;
		bool			good;
		ProcessRequest  processRequest;

		ClientInfo( void ) {};
		ClientInfo( int sockfd );
		~ClientInfo( void );
		ClientInfo( const ClientInfo& rhs );
		ClientInfo&	operator=( const ClientInfo& rhs );


		void	      	parserequest( std::string  request );
		bool			sendResponse( void );
		bool    	  	readyToResponse( pollfd structpoll );
};