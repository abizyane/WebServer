/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:06:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/11 12:03:37 by abizyane         ###   ########.fr       */
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
	if (_locations != NULL) {
		for (std::map<std::string, LocationConf*>::iterator it = _locations->begin(); it != _locations->end(); it++){
			delete it->second;
		}
	}
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

bool	ServerConf::hasHostName( const std::string& hostname ) const
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


// bool	ServerConf::hasLocation( std::string path )
// {
// 	if (!_locations)
// 		return false;
// 	return ( _locations->find(path) != _locations->end() );
// }

std::string		ServerConf::getErrPage( int code, const std::string& defaultPag )
{
	if (_errorPage == NULL)
		return (defaultPag);
	std::string ans;
	std::map<int, std::string>::iterator it = _errorPage->find(code);
	if (it != _errorPage->end()) {
		std::string path = ((this->_root == NULL) ? "" : *this->_root) + it->second;
		std::ifstream	file(path.c_str(), std::ios::in | std::ios::binary);
		if (file.is_open() && std::getline(file, ans, '\0'))
			return ans;
	}
	return ans;
}

void	ServerConf::passDirectiveToRoutes( void )
{
	if (_locations == NULL)
		return;
	std::map<std::string, LocationConf*>::iterator first = _locations->begin();
	std::map<std::string, LocationConf*>::iterator last = _locations->end();
	for (; first != last; first++) {
		if (this->hasDirective("root") && !first->second->hasDirective("root")) {
			first->second->setRoot(*this->_root);
			first->second->markDirective("root");
		}
		if (this->_uploadStore != NULL && !first->second->hasDirective("upload_store")) {
			first->second->setUploadStore(*this->_uploadStore);
			first->second->markDirective("upload_store");
		}
		if (!first->second->hasDirective("autoindex")) {
			first->second->setAutoIndex(this->_autoIndex);
			first->second->markDirective("autoindex");
		}
		if (!first->second->hasDirective("clientBody")) {
			first->second->setClientBody(this->_clientMaxBody);
			first->second->markDirective("clientBody");
		}
		if (this->_errorPage != NULL) {
			std::map<int, std::string>::iterator it = _errorPage->begin();
			std::map<int, std::string>::iterator ite = _errorPage->end();
			for (; it != ite; it++) {
				if (!first->second->hasDirective("error_page:" + to_str(it->first))) {
					first->second->addErrorPage(it->first, it->second);
					first->second->markDirective("error_page:" + to_str(it->first));
				}
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
		first->second->passDirectiveToRoutes();
	}
}

LocationConf*	ServerConf::getUri( std::string uri ) const
{
    uri = normPath(uri);
	if (_locations == NULL)
		return NULL;
    while (uri != "") {
		if (_locations->find(uri) != _locations->end())
			return (*_locations)[uri];

		std::map<std::string, LocationConf*>::iterator it = _locations->begin();
		std::map<std::string, LocationConf*>::iterator ite = _locations->end();

		for (; it != ite; it++) {
			LocationConf*	ans = it->second->getUri(uri);
			if (ans != NULL) return ans;
		}

        std::size_t pos = uri.find_last_of('/');
        if (pos != std::string::npos) {
            uri = uri.substr(0, pos + (pos == 0));
        }
    }
    return NULL;
}
