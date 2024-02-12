/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:35:31 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 12:27:22 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP.hpp"


HTTP::HTTP( void ) : _root(NULL), _errorPage(NULL), _allowed(NULL),
	_index(NULL), _uploadStore(NULL), _autoIndex(false), _clientMaxBody(10)
{
}

HTTP::~HTTP( void )
{
	delete	_root;
	delete	_errorPage;
	delete	_allowed;
	delete	_index;
	delete	_uploadStore;
}

HTTP::HTTP( HTTP const& rhs ) : _root(NULL), _errorPage(NULL), _allowed(NULL),
	_index(NULL), _uploadStore(NULL), _autoIndex(false), _clientMaxBody(10)
{
	*this = rhs;
}

HTTP&	HTTP::operator=( const HTTP& rhs )
{
	if (this == &rhs) return *this;
	(delete _root, _root = NULL);
	if (rhs._root != NULL)
		_root = new std::string(*rhs._root);
	(delete	_errorPage, _errorPage = NULL);
	if (rhs._errorPage != NULL)
		_errorPage = new std::map<int, std::string>(*rhs._errorPage);
	(delete	_allowed, _allowed = NULL);
	if (rhs._allowed != NULL)
		_allowed = new std::set<std::string>(*rhs._allowed);
	(delete	_index, _index = NULL);
	if (rhs._index != NULL)
		_index = new std::vector<std::string>(*rhs._index);
	(delete	_uploadStore, _uploadStore = NULL);
	if (rhs._uploadStore != NULL)
		_uploadStore = new std::string(*rhs._uploadStore);
	_autoIndex = rhs._autoIndex;
	_clientMaxBody = rhs._clientMaxBody;
	return *this;
}

void	HTTP::allowMethod( const std::string& method ) 
{
	if (_allowed == NULL)
		_allowed = new std::set<std::string>();
	_allowed->insert(method);
}

void	HTTP::denyMethod( const std::string& method ) 
{
	if (_allowed == NULL)
		return;
	if (_allowed->find(method) != _allowed->end())
		_allowed->erase(method);
}

void	HTTP::setRoot( const std::string& root ) 
{
	// TODO: handle routing join
	if (_root == NULL)
		_root = new std::string();
	*_root = root;
}

void	HTTP::setUploadStore( const std::string& uploadSotore ) 
{
	// TODO: handle routing join
	if (_uploadStore == NULL)
		_uploadStore = new std::string();
	*_uploadStore = uploadSotore;
}

void	HTTP::addIndex( const std::string& index ) 
{
	if (_index == NULL)
		_index = new std::vector<std::string>();
	_index->push_back(index);
}

void	HTTP::setAutoIndex( bool autoIndex ) 
{
	_autoIndex = autoIndex;	
}

void	HTTP::addErrorPage( int code, const std::string& page ) 
{
	if (_errorPage == NULL)
		_errorPage = new std::map<int, std::string>();
	(*_errorPage)[code] = page;
}

void	HTTP::setClientBody( size_t size ) 
{
	_clientMaxBody = size;
}
