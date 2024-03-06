/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 06:31:51 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/Parser.hpp"
// #include "Core/Server/Server.hpp"
#include "Core/CoreServer.hpp"
#include "Configuration/MainConf.hpp"


void	handler( int sig )
{
	(void)sig;
	std::cout << "\b\b" << strTime() << " exiting server...." << std::endl;
	sleep(1);
	delete CoreServer::getCore();
	delete MainConf::getConf();
	exit(0);
}

int main()
{
	CoreServer	*core = CoreServer::getCore();

	signal(SIGINT, handler);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, handler);
	try {
		Parser	parser;
		parser.parse();
	} catch (std::exception & e) {
		std::cout << strTime() << e.what() << std::endl;
	}
	core->init();
	core->run();
	delete CoreServer::getCore();
	delete MainConf::getConf();
}
