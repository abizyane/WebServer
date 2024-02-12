/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:00:37 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 12:14:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ServerConf_HPP_
#define _ServerConf_HPP_

#include <iostream>
#include "HTTP.hpp"
#include "LocationConf.hpp"

class	ServerConf : public HTTP
{
	private:
		std::set<std::string>					*_hostNames;
		std::set<unsigned int>					*_ports;
		std::map<std::string, LocationConf*>	*_locations;

		ServerConf&	operator=( const ServerConf& rhs );
	public:
		ServerConf( void );
		~ServerConf( void );
		ServerConf( ServerConf const& rhs );

		void	addHostName( const std::string& hostName );
		void	addPort( unsigned int port );
		void	addLocation( const std::string& url, LocationConf* location );
};

#endif
