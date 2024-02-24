/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:19:53 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/24 16:53:38 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void		Server::init()
{
	MainConf	*conf = MainConf::getConf();
	std::set<unsigned int>	ports = conf->getAllPorts();
	std::set<unsigned int>::iterator itb = ports.begin(), ite = ports.end();
	for (; itb != ite; itb++) {
		Socket *sock = new Socket();
		try {
			sock->open();
			sock->bind("0.0.0.0", *itb);
			sock->setToNonBlock();
			sock->listen();
			std::cout << "start listening on: " << "0.0.0.0:" << *itb << '\n';
			_poller.push(sock->fileno());
			_listeners.push_back(sock);
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
			delete sock;
		}
	}
	_nServ = _listeners.size();
}

void	Server::_acceptNewClients( void ) 
{
	for (int i = 0; i < _nServ; i++) {
		if (_poller[i].revents & POLLIN) {
			Socket	*sock = new Socket();
			try {
				sock = _listeners[i]->accept();
 				sock->setToNonBlock();
				_tempPoller.push(sock->fileno(), POLLIN | POLLOUT);
				_clients[sock->fileno()] = new Client(sock);
				std::cout << "new client accepted" << '\n';
			} catch (std::exception& e) {
				// delete client;
				delete sock;
				std::cerr << "error accepting new connection " << std::endl;
			}
		}
	}
}


void	Server::_handleClients( void ) 
{
	for (size_t i = _nServ; i < _poller.size(); i++) {
		if (_poller[i].revents & POLLIN) {
			if (_clients[_poller[i].fd]->setRequest() == false) {
				_erasedClients.push_back(i);
				std::cout << "client disconnected" << std::endl;
			}
		}
		// write events
		if (_poller[i].revents & POLLOUT) {
			if (_clients[_poller[i].fd]->responseIsDone()) {
				_clients[_poller[i].fd]->sendResponse();
				// _poller.erase()
			}
		}
		if (_poller[i].revents & POLLHUP) {
			_clients.erase(_poller[i].fd);
			_poller.erase(_poller.begin() + i);
			std::cout << "client disconnected" << std::endl;
		}
	}
}

void	Server::_eraseClients( void ) 
{
	for (size_t i = 0; i < _erasedClients.size(); i++) {
		int idx = _erasedClients[i];
		_clients.erase(_tempPoller[idx].fd);
		_tempPoller.erase(_tempPoller.begin() + idx);
	}
}

void		Server::run()
{
	while (_nServ) {
		if (_poller.poll() <= 0)
			continue;
		_tempPoller = _poller;
		_acceptNewClients();
		_handleClients();
		_eraseClients();
		_poller = _tempPoller;
	}
}


/*
 poller: 1 2 3 4 => 1 2 3 4
 _temp : 1 2 3 4 => 1 2 4 5
*/