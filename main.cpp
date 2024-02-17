/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/16 18:16:01 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/Parser.hpp"
#include "Core/Server.hpp"
#include "Configuration/MainConf.hpp"


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
}