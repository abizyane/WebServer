/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 09:45:12 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/02 14:14:53 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( void ) {
}

void	Server::init( void ) {
	std::set<unsigned int>	ports =	MainConf::getConf()->getAllPorts();
	std::set<unsigned int>::iterator first = ports.begin(), last = ports.end();
	for (; first != last; first++) {
		Socket* sock = new Socket();
		try {
			sock->open();
			sock->setToNonBlock();
			sock->bind("0.0.0.0", *first);
			sock->listen();
			std::cout << "start listening on 0.0.0.0:" << *first << " ..." << std::endl;
			_poller.push(sock->fileno());
			_sockets.push_back(sock);
		} catch (std::exception& e){
			delete sock;
			std::cerr << e.what() << std::endl;
		}
	}
	nServ = _sockets.size();
}

void	Server::_acceptNewClients( void ) {
	for (size_t i = 0; i < nServ; i++) {
		if (_poller[i].revents & POLLIN) {
			try {
				Socket* sock = _sockets[i]->accept();
				sock->setToNonBlock();
				_tempPoller.push(sock->fileno(), POLLIN | POLLOUT);
				_clients[sock->fileno()] = new Client(sock);
				std::cout << "new client connected" << std::endl;
			} catch (std::exception & e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}
}

void	Server::_purgeClient( int idx ) {
	int fd = _tempPoller[idx].fd;
	Client* client = _clients[fd];
	_clients.erase(fd);
	delete client;
	_tempPoller[idx].fd = -1;
	std::cout << "client disconnected" << std::endl;
}

void	Server::_manageClients( void ) {
	for (size_t i = nServ; i < _poller.size(); i++) {
		Client* client = _clients[_poller[i].fd];
		if (_poller[i].revents & POLLIN) {
			try {
				if (client->consumStream() == false)
					_purgeClient(i);
				// else
					// std::cout << "request recieved from client" << std::endl;
			} catch (std::exception & e) {
				std::cerr << e.what() << std::endl;
			}
		} else if (_poller[i].revents & POLLOUT) {// until request parseIsDone
			client->sendResponse();
			if (client->ResponseSent())
				_purgeClient(i);
		}
		else if (_poller[i].revents & POLLHUP)
			_purgeClient(i);
	}
}

void	Server::run( void ) {
	while (true) {
		_tempPoller = _poller;
		if (_poller.poll() <= 0)
			continue;
		_acceptNewClients();
		_manageClients();
		_eraseInactiveClients();
		_poller = _tempPoller;
		// std::cout << "number of clients: " << _clients.size() << std::endl;
	}
}

void Server::_eraseInactiveClients() {
    for (Poller::iterator it = _tempPoller.begin(); it != _tempPoller.end(); ) {
        if (it->fd == -1) {
            it = _tempPoller.erase(it);
        } else {
            ++it;
        }
    }
}

Server::~Server( void ) {
	// delete server sockets:
	for (size_t i = 0; i < _sockets.size(); i++)
		delete _sockets[i];
	std::map<int, Client*>::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
		delete it->second;
}

