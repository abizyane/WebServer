/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainConf.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:25:47 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 15:04:03 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MainConf_HPP_
#define _MainConf_HPP_

#include <iostream>
#include "HTTP.hpp"
#include "LocationConf.hpp"
#include "ServerConf.hpp"


class	MainConf : public HTTP
{
	private:
		std::vector<ServerConf*>	_servers;
		static	MainConf*	_instance;

		MainConf&	operator=( const MainConf& rhs );
		MainConf( void );
	public:
		~MainConf( void );

		static	MainConf*	getConf( void );
		
		void	addServer( ServerConf* server );
	
		// ServerConf*	getServerByHostPort(int	port, std::string host);
};

#endif
