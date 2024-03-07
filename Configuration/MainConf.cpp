/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainConf.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 23:22:05 by nakebli          ###   ########.fr       */
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

void	MainConf::passDirectiveToServers( void ) {
	for (size_t idx = 0; idx < _servers.size(); idx++) {
		if (this->hasDirective("root") && _servers[idx]->hasDirective("root") == false) {
			_servers[idx]->setRoot(*this->_root);
			_servers[idx]->markDirective("root");
		}
		if (this->_uploadStore != NULL && !_servers[idx]->hasDirective("upload_store")) {
			_servers[idx]->setUploadStore(*this->_uploadStore);
			_servers[idx]->markDirective("upload_store");
		}
		if (!_servers[idx]->hasDirective("autoindex")) {
			_servers[idx]->setAutoIndex(this->_autoIndex);
			_servers[idx]->markDirective("autoindex");
		}
		if (!_servers[idx]->hasDirective("clientBody")) {
			_servers[idx]->setClientBody(this->_clientMaxBody);
			_servers[idx]->markDirective("clientBody");
		}
		if (this->_errorPage != NULL) {
			std::map<int, std::string>::iterator it = _errorPage->begin();
			std::map<int, std::string>::iterator ite = _errorPage->end();
			for (; it != ite; it++) {
				if (!_servers[idx]->hasDirective("error_page:" + toString(it->first))) {
					_servers[idx]->addErrorPage(it->first, it->second);
					_servers[idx]->markDirective("error_page:" + toString(it->first));
				}
			}
		}
		if (this->_allowed != NULL) {
			std::set<std::string>::iterator it = _allowed->begin();
			std::set<std::string>::iterator ite = _allowed->end();
			for (; it != ite; it++)
				_servers[idx]->allowMethod(*it);
		}
		if (this->_index != NULL) {
			std::vector<std::string>::iterator it = _index->begin();
			std::vector<std::string>::iterator ite = _index->end();
			for (; it != ite; it++)
				_servers[idx]->addIndex(*it);
		}
		_servers[idx]->passDirectiveToRoutes();
	}
}

ServerConf*		MainConf::getServerByPortHost(int port, std::string host) {
	std::vector<ServerConf*>::iterator it = _servers.begin();
	ServerConf* server = NULL;
	for (; it != _servers.end(); it++)
	{
		if ((*it)->hasHostName(host))
			return *it;
		if ((*it)->hasPort(port))
			return server = *it;
	}
	return NULL;
}