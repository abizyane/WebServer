/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:33:00 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/20 10:30:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Parser_HPP_
#define _Parser_HPP_

#include <iostream>
#include "Token.hpp"
#include "Lexer.hpp"
#include "../Configuration/MainConf.hpp"
#include "../utils/utils.hpp"
#include <sstream>
#include <exception>


class	Parser
{
	private:
		Lexer		_lex;
		Token		_currTok;
		MainConf*	conf;

		
		Parser( Parser const& rhs );
		Parser&	operator=( const Parser& rhs );
		
		/* parse functions : */
		
		void	_parseRoot(HTTP& httpConf);
		void	_parseErrorPage(HTTP& httpConf);
		void	_parseMethods(HTTP& httpConf);
		void	_parseIndex(HTTP& httpConf);
		void	_parseUpload(HTTP& httpConf);
		void	_parseAutoIndex(HTTP& httpConf);
		void	_parseClientBody(HTTP& httpConf);
		// LocationConf*	_parseLocation(HTTP& httpConf);
		// void	_parseLocation(ServerConf& server);
		// void	_parseLocation(LocationConf& location);
		void	_parseHost(ServerConf& server);
		void	_parsePort(ServerConf& location);
		std::pair<std::string, LocationConf*>	_parseLocation( ServerConf& parentServer, std::string parentUri = "" );
		ServerConf*		_parseServer( void );
		
		void	_parseCgi( LocationConf& location );
		void	_parseRedirect( LocationConf& location );
		
		void	_advance( Token tok );
		void	_duplicateError(const std::string& directive);
		
	public:
		Parser( void );
		~Parser( void );
		void	parse( void );
};

#endif
