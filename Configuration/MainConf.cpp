/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainConf.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/16 17:56:59 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainConf.hpp"

MainConf*	MainConf::_instance = NULL;

MainConf::MainConf( void ) : HTTP()
{
}

MainConf::~MainConf( void )
{
	// TODO: delete all servers
}


MainConf&	MainConf::operator=( const MainConf& rhs )
{
	if (this != &rhs){
		HTTP::operator=(rhs);
	}
	return (*this);
}

MainConf*	MainConf::getConf( void )
{
	if (_instance == NULL)
		_instance = new MainConf();
	return _instance;
}

void	MainConf::addServer( ServerConf* server )
{
	_servers.push_back(server);
}

std::set<unsigned int>	MainConf::getAllPorts( void ) const
{
	std::set<unsigned int> allports;
	std::vector<ServerConf*>::const_iterator	it = _servers.begin();
	for (; it != _servers.end(); it++)
		(*it)->getPorts(allports);
	return (allports);
}

//	Could be used later ... 

const std::vector<ServerConf*>	&MainConf::getServersConf( void ) const
{
	return (_servers);
}