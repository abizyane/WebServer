/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConf.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:36:53 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/13 09:21:34 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConf.hpp"


LocationConf::LocationConf( void ) : HTTP(), _locations(NULL), _extentions(NULL)
	, _redirect(NULL)
{
}

LocationConf::LocationConf( HTTP const& rhs ) : HTTP(rhs), _locations(NULL), _extentions(NULL)
	, _redirect(NULL)
{
}

LocationConf::~LocationConf( void )
{
	delete	_locations;
	delete	_extentions;
	delete 	_redirect;
}

LocationConf::LocationConf( LocationConf const& rhs ) : HTTP(rhs), _locations(NULL), _extentions(NULL)
	, _redirect(NULL)
{
}

LocationConf&	LocationConf::operator=( const LocationConf& rhs )
{
	if (this != &rhs){
		HTTP::operator=(rhs);
	}
	return (*this);
}

void	LocationConf::addLocation( const std::string& url, LocationConf* location )
{
	if (_locations == NULL)
		_locations = new std::map<std::string, LocationConf*>();
	(*_locations)[url] = location;
}

void	LocationConf::addExtention( const std::string& extention )
{
	if (_extentions == NULL)
		_extentions = new std::set<std::string>();
	_extentions->insert(extention);
}

void	LocationConf::addRedirectpage( int code, const std::string& page )
{
	if (_redirect == NULL)
		_redirect = new std::pair<int, std::string> ();
	_redirect->first = code;
	_redirect->second = page;
}

bool	LocationConf::cgiIsAllowed( void ) const
{
	return _extentions != NULL;
}

bool	LocationConf::hasRedirect( void ) const
{
	return	_redirect != NULL; 	
}

