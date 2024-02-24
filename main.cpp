/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/24 14:57:51 by zel-bouz         ###   ########.fr       */
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
	try {
		Parser	parser;
		parser.parse();
		// MainConf *main = MainConf::getConf();
		// const std::vector<ServerConf*> servers = main->getServersConf();
		// for (size_t i = 0; i < servers.size(); i++) {
		// 	LocationConf* loc = servers[i]->getUri("/blog/home");
		// 	if (loc != NULL) {
		// 		std::cout << "root: " << loc->getRoot() << '\n';
		// 	}
		// }
		Server server;
		server.init();
		server.run();
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	}
	delete MainConf::getConf();
}