/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:32:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 14:54:18 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Token_HPP_
#define _Token_HPP_

#include <iostream>
#include <fstream>
#include <map>

class	Token
{
	public:
		typedef	enum {
			WORD, HTTP, SERVER, LOCATION, HOST, PORT, ROOT, ALLOW, DENY, 
			INDEX, AUTO, ERR_PAGE, BODY_SIZE, UPLOAD, CGI, RETURN,
			OPEN_CURLY, CLOSE_CURLY, SEMICOLEN, _EOF
		}	token;

	private:
		token								_type;
		std::string							*_data;
		static std::map<token, std::string>	_keys;

	public:
		Token( token );
		Token( void );
		Token( const std::string& data );
		~Token( void );
		Token( Token const& rhs );
		Token&	operator=( const Token& rhs );
		
		bool		isKeyWord( void ) const;
		std::string	data( void ) const;
		token		type( void ) const;
		bool		operator==(const Token& rhs) const;
		bool		operator!=(const Token& rhs) const;
		friend	std::ostream&	operator<<(std::ostream& os, const Token& rhs);
};

#endif
