/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/20 11:45:17 by nakebli          ###   ########.fr       */
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
		Server	*server = new Server();
		server->printSockets();
		server->printPollfds();
		server->ServerCoreHandle();
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cerr << "..." << '\n';
	}
	delete MainConf::getConf();
}