/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:40:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/14 10:37:39 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/Parser.hpp"

int main()
{
	Parser	parser;
	try {
		parser.parse();
	} catch (std::exception & e) {
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cerr << "..." << '\n';
	}
}