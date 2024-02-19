/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:06:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/16 14:29:46 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConf.hpp"


ServerConf::ServerConf( void ) : HTTP(), _hostNames(NULL), _ports(NULL), _locations(NULL)
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
	if (_locations == NULL) {
		_locations = new std::map<std::string, LocationConf*>();
	}
	(*_locations)[url] = location;
}

// newly implemented 

bool	ServerConf::hasHostName( const std::string hostname ) const
{
	if (_hostNames == NULL)
		return (false);
	std::set<std::string>::iterator it = _hostNames->find(hostname);
	return (it != _hostNames->end());
}

bool	ServerConf::hasPort( const int& port) const
{
	if ( _ports == NULL )
		return (false);
	std::set<unsigned int>::iterator it = _ports->find(port);
	return (it != _ports->end());
}

void	ServerConf::getPorts( std::set<unsigned int>& ports )
{
	if (_ports == NULL)
		return ;
	std::set<unsigned int>::iterator it = _ports->begin();
	for (; it != _ports->end(); it++)
		ports.insert(*it);
}