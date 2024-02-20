/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConf.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:36:53 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/20 11:12:43 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConf.hpp"
#include "../utils/utils.hpp"


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

bool	LocationConf::hasCgi( void ) const
{
	return _extentions != NULL;
}

bool	LocationConf::hasRedirect( void ) const
{
	return	_redirect != NULL; 	
}

// new implemented :

bool	LocationConf::hasExtention( const std::string& extention )
{
	return _extentions != NULL && _extentions->find(extention) != _extentions->end();
}

std::string		LocationConf::getRoot( void ) const
{
	return ((_root != NULL) ? *_root : "");
}

std::string		LocationConf::getUploadStore( void ) const 
{
	return ((_uploadStore != NULL) ? *_uploadStore : "");
}

std::string		LocationConf::getErrPage( int code, const std::string& defaultPag )
{
	if (_errorPage == NULL)
		return (defaultPag);
	std::map<int, std::string>::iterator it = _errorPage->find(code);
	return ((it == _errorPage->end()) ? defaultPag : it->second);
}

bool	LocationConf::methodIsAllowed( const std::string& method) const
{
	if (_allowed == NULL)
		return (false);
	std::set<std::string>::iterator it = _allowed->find( method );
	return (it != _allowed->end());
}

bool	LocationConf::dirListingEnabled() const
{
	return (_autoIndex);
}

size_t	LocationConf::getClientBodySize( void ) const
{
	return (_clientMaxBody);
}

void	LocationConf::passDirectiveToRoutes( void )
{
	std::map<std::string, LocationConf*>::iterator first = _locations->begin();
	std::map<std::string, LocationConf*>::iterator last = _locations->end();
	for (; first != last; first++) {
		if (this->hasDirective("root") && !first->second->hasDirective("root"))
			first->second->setRoot(*this->_root);
		if (this->_uploadStore != NULL && !first->second->hasDirective("upload_store"))
			first->second->setUploadStore(*this->_uploadStore);
		if (!first->second->hasDirective("autoindex"))
			first->second->setAutoIndex(this->_autoIndex);
		if (!first->second->hasDirective("clientBody"))
			first->second->setClientBody(this->_clientMaxBody);
		if (this->_errorPage != NULL) {
			std::map<int, std::string>::iterator it = _errorPage->begin();
			std::map<int, std::string>::iterator ite = _errorPage->end();
			for (; it != ite; it++) {
				if (!first->second->hasDirective("error_page:" + toString(it->first)))
					first->second->addErrorPage(it->first, it->second);
			}
		}
		if (this->_allowed != NULL) {
			std::set<std::string>::iterator it = _allowed->begin();
			std::set<std::string>::iterator ite = _allowed->end();
			for (; it != ite; it++)
				first->second->allowMethod(*it);
		}
		if (this->_index != NULL) {
			std::vector<std::string>::iterator it = _index->begin();
			std::vector<std::string>::iterator ite = _index->end();
			for (; it != ite; it++)
				first->second->addIndex(*it);
		}
		if (_locations != NULL) {
			std::set<std::string>::iterator it = _extentions->begin();
			std::set<std::string>::iterator ite = _extentions->end();
			for (; it != ite; it++)
				first->second->addExtention(*it);
		}
		first->second->passDirectiveToRoutes();
	}
}