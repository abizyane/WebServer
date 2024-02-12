/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:06:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 12:17:41 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConf.hpp"


ServerConf::ServerConf( void ) : HTTP(), _hostNames(NULL), _ports(NULL)
{
}

ServerConf::~ServerConf( void )
{
	delete	_hostNames;
	delete	_ports;
	delete	_locations;
}

ServerConf::ServerConf( ServerConf const& rhs ) : HTTP(rhs), _hostNames(NULL), _ports(NULL) 
	,_locations(NULL)
{
}

ServerConf&	ServerConf::operator=( const ServerConf& rhs )
{
	if (this != &rhs){
		HTTP::operator=(rhs);
	}
	return (*this);
}

void	ServerConf::addHostName( const std::string& hostName )
{
	if (_hostNames == NULL)
		_hostNames = new std::set<std::string>();
	_hostNames->insert(hostName);
}

void	ServerConf::addPort( unsigned int port )
{
	if (_ports == NULL)
		_ports = new std::set<unsigned int>();
	_ports->insert(port);
}

void	ServerConf::addLocation( const std::string& url, LocationConf* location )
{
	if (_locations == NULL)
		_locations = new std::map<std::string, LocationConf*>();
	(*_locations)[url] = location;
}

