/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:19:53 by nakebli           #+#    #+#             */
/*   Updated: 2024/02/21 13:09:23 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	MainConf*	conf = MainConf::getConf();
	std::set<unsigned int>	ports = conf->getAllPorts();

	std::set<unsigned int>::iterator	first = ports.begin();
	std::set<unsigned int>::iterator	last = ports.end();
	for ( ; first != last; first++ ) {
		Socket	sock;
		sockaddr_in	addr;
		addr.sin_addr.s_addr = inet_addr("0.0.0.0");
		addr.sin_family = AF_INET;
		addr.sin_port = htons(*first);
		if (sock.bind((sockaddr*)&addr, sizeof(addr)) == false) {
			std::cerr	<< "Error binding socket to port: " << *first
						<< " : " << std::strerror(errno) << '\n';
			continue;
		}
		if (sock.listen() == false) {
			std::cerr	<< "Error listning socket to port: " << *first 
						<< " : " << std::strerror(errno) << '\n';
			continue;
		}
		_sockets.push_back(sock);
		_pollfds.pushFd(sock.getFd());
	}
	// TODO: free befor exit
	if (!_sockets.size())
		exit(0);
}

ClientIter	Server::findClient(int fd)
{
	if (_clients.empty()) return _clients.end();
	ClientIter client = _clients.begin();
	for (; client != _clients.end(); client++)
	{
		if (fd == (*client)->fd)
			break ;
	}
	return (client);
}

SockIter	Server::findServerSock( int fd )
{
	std::vector<Socket>::iterator sock = _sockets.begin();
	for (; sock != _sockets.end(); sock++)
		if (sock->getFd() == fd)
			break;
	return sock;
}

void			Server::handleListner( pollfd structpoll )
{
	if (structpoll.revents & POLLERR)
		std::cerr << "POLLERR cought\n";
	else if (structpoll.revents & POLLHUP)
		std::cerr << "POLLHUP cought\n";
	else if (structpoll.revents & POLLERR)
		std::cerr << "POLLERR cought\n";
	else if ((structpoll.revents & POLLIN) == POLLIN)
	{
		ClientInfo *client = new ClientInfo(structpoll.fd);
		_pollfds.pushFd(client->fd);
		_clients.push_back(client);
	}
}

bool			Server::handleRequest( pollfd structpoll )
{
	ClientIter	client = findClient( structpoll.fd );
	char    buffer[4096] = {0};
    int rcv = recv((*client)->fd, buffer, sizeof(buffer), 0);
	if (rcv < 0)
	{
		std::cerr	<< "error recieving client request: "
					<< strerror(errno) << std::endl;
		return false;
	}
	else if (rcv == 0)
	{
		close ((*client)->fd);
		_clients.erase(client);
		_pollfds.erase((*client)->fd);
		return false;
	}
	else
	{
		(*client)->parserequest(buffer);
		if ((*client)->readyToResponse(structpoll))
		{
			if (!(*client)->sendResponse())
			{
				std::cout << "nothing sent \n";
				return false;
			}
		}
		return true;
	}
}

//	TODO : IMPLEMET 

void	Server::ServerCoreHandle( void )
{
	while (true)
	{
		signal(SIGPIPE, SIG_IGN);
		if (!_pollfds.poll())
			continue ;
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (i < _sockets.size() /* findServerSock(_pollfds[i].fd) */) // if the socket is a server (listner) socket 
				handleListner(_pollfds[i]);
			else if (_pollfds[i].revents & POLLIN) // if it's a client socket
			{
				if (!handleRequest(_pollfds[i]))
					continue ;
			}
		}
	}
}

bool	Server::isGood()
{
	return (_sockets.size() != 0);
}

void	Server::printSockets()
{
	std::cout << "Sockets : \n";
	SockIter it = _sockets.begin();
	while (it != _sockets.end())
	{
		std::cout << "socket fd : " << it->getFd() << std::endl;
		it ++;
	}
}

void	Server::printPollfds()
{
	_pollfds.printFds();
}
