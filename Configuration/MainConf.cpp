/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainConf.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 12:27:47 by zel-bouz         ###   ########.fr       */
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
