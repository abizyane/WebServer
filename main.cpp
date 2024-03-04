/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/01 19:05:00 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/Parser.hpp"
// #include "Core/Server/Server.hpp"
#include "Core/CoreServer.hpp"
#include "Configuration/MainConf.hpp"

int main()
{
	Parser	parser;
	try {
		parser.parse();
		// MainConf *main = MainConf::getConf();
		// const std::vector<ServerConf*> servers = main->getServersConf();
		// for (size_t i = 0; i < servers.size(); i++) {
		// 	LocationConf* loc = servers[i]->getUri("/blog/home");
		// 	if (loc != NULL) {
		// 		std::cout << "root: " << loc->getRoot() << '\n';
		// 	}
		// }
		CoreServer server;
		server.init();
		server.run();
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cerr << "..." << '\n';
	}
}
