#pragma once

#include "Server.hpp"
#include "../Configuration/MainConf.hpp"

class	CoreServer
{
	private:
		std::vector<Server*>	_servers;
		Selector				_selector;

		inline int	_nfds( void ) {
			int ans = -1;
			for (size_t i = 0; i < _servers.size(); i++) {
				ans = std::max(ans, _servers[i]->fileno());
				for (size_t	j = 0; j < _servers[i]->_clients.size(); j++) {
					ans = std::max(ans, _servers[i]->_clients[j]->fileno());
					ans = std::max(ans, _servers[i]->_clients[j]->writefd());
					ans = std::max(ans, _servers[i]->_clients[j]->readfd());
				}
			}
			return ans;
		}

		void _acceptNewClient( Server* server ) {
			sockaddr_in	info;
			socklen_t	len = 0;
			memset(&info, 0, sizeof(sockaddr_in));
			info.sin_port = htons(server->getInfo().sin_port);
			int ans = accept(server->fileno(), (sockaddr*)&info, &len);
			if (ans == -1)
				throw std::runtime_error("accept() faild");
			if (fcntl(ans, F_SETFL, O_NONBLOCK) < 0)
				throw std::runtime_error("fcntl() faild");
			server->_clients.push_back(new Client(_selector, ans, info));
			// _selector.set(ans, Selector::WR_SET | Selector::RD_SET);
		}

	public:
		CoreServer( void ) {
		};

		void	init( void ) {
			std::set<unsigned int>	_ports = MainConf::getConf()->getAllPorts();
			for (std::set<unsigned int>::iterator it = _ports.begin(); it != _ports.end(); it++)
			{
				Server* server = new Server(_selector);
				try {
					server->init("0.0.0.0", *it);
					std::cout << "start listening on [0.0.0.0:" << *it << "]" << std::endl;
					_servers.push_back(server);
				} catch (std::exception & e) {
					delete server;
					std::cout << "port: [" << *it << "]: " << e.what() << std::endl;
				}

			}
		}

		void run() {
			while (!_servers.empty()) {
				int maxfds = _nfds();
				if (_selector.select(maxfds + 1) == false)
					continue;

				for (size_t i = 0; i < _servers.size(); i++) {
					Server* server = _servers[i];

					if (_selector.isReadable(server->fileno()) &&  maxfds < 1000) {
						try {
							_acceptNewClient(server);
							std::cout << "new client accepted" << std::endl;
						} catch (std::exception & e) {
							std::cout << e.what() << std::endl;
						}
					}

					for (std::vector<Client*>::iterator it = server->_clients.begin(); it != server->_clients.end(); ) {
						Client* client = *it;

						if (_selector.isReadable(client->fileno())) {
							char buff[1024] = {0};
							int ret = ::recv(client->fileno(), buff, 1024, 0);
							if (ret == -1) {
								perror("recv");
							} else if (ret == 0) {
								std::cout << "client disconnected" << std::endl;
								// close(client->fileno()); // Close socket
								delete client;
								it = server->_clients.erase(it);
								continue;
							} else {
								client->readRequest(buff, ret);
							}
						}

						if (_selector.isWriteable(client->fileno())) {
							if (client->sendResponse()) {
								std::cout << "client disconnected" << std::endl;
								delete client;
								it = server->_clients.erase(it);
								continue;
							}
						}

						++it;
					}
				}
			}
		}
};