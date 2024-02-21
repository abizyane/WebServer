/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/21 18:57:42 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/Parser.hpp"
#include "Core/Server.hpp"
#include "Configuration/MainConf.hpp"


void	lk()
{
	system("leaks main");
}


int main()
{
	Parser	parser;
	try {
		parser.parse();
		MainConf *main = MainConf::getConf();
		const std::vector<ServerConf*> servers = main->getServersConf();
		for (size_t i = 0; i < servers.size(); i++) {
			LocationConf* loc = servers[i]->getUri("/blog/home");
			if (loc != NULL) {
				std::cout << loc->getRoot() << '\n';
			}
		}
		// std::vector<ServerConf*>::const_iterator it = main->getServersConf().cbegin();
		// while (it != main->getServersConf().cend())
		// {
		// 	LocationConf *loc = (*it)->getUri("/blog/home");
		// 	if (loc)
		// 		std::cout << loc->getRoot() << std::endl;
		// 	std::cout << "ended \n";
		// 	it++;
		// }
		// Server	*server = new Server();
		// server->printSockets();
		// server->printPollfds();
		// server->ServerCoreHandle();
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cerr << "..." << '\n';
	}
	delete MainConf::getConf();
}