/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:40:01 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 14:59:22 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

std::map<Token::token, std::string>	initKeys( void )
{
	std::map<Token::token, std::string>	ans;
	Token::token	toks[] = {
		Token::WORD, Token::HTTP, Token::SERVER, Token::LOCATION, Token::HOST, Token::PORT, 
		Token::ROOT, Token::ALLOW, Token::DENY, Token::INDEX, Token::AUTO, Token::ERR_PAGE,
		Token::BODY_SIZE, Token::UPLOAD, Token::CGI, Token::RETURN,
		Token::OPEN_CURLY, Token::CLOSE_CURLY, Token::SEMICOLEN, Token::_EOF
	};
	std::string		vals[] = {
		"word", "http", "server", "location", "host", "port", "root", "allow", "deny",
		"index", "autoindex", "error_page", "client_body_max_size", "upload_store", "cgi", "return",
		"{", "}", ";", "EOF"
	};
	const int N = sizeof(toks) / sizeof(toks[0]);
	for (int i = 0; i < N; i++) {
		ans[toks[i]] = vals[i];
	}
	return ans;
}

std::map<Token::token, std::string>	Token::_keys = initKeys();

Token::Token( void ) : _type(Token::_EOF), _data(NULL)
{
}

Token::Token( Token::token type ) : _type(type), _data(NULL)
{
}

Token::Token( const std::string& data ) : _type(Token::WORD)
{
	_data = new std::string(data);
}

Token::~Token( void )
{
	delete _data;
}

Token::Token( Token const& rhs ) : _data(NULL)
{
	*this = rhs;
}

Token&	Token::operator=( const Token& rhs )
{
	if (this != &rhs){
		_type = rhs._type;
		(delete _data, _data = NULL);
		if (rhs._data != NULL)
			_data = new std::string(*rhs._data);
	}
	return (*this);
}

std::string	Token::data( void ) const
{
	return _data != NULL ? *_data : "";
}

Token::token	Token::type( void ) const
{
	return _type;
}

bool	Token::isKeyWord( void ) const {
	return _type != WORD && _type != OPEN_CURLY && _type != CLOSE_CURLY && _type != SEMICOLEN && _type != _EOF;
}

bool	Token::operator==(const Token& rhs) const
{
	return _type == rhs._type;
}
bool	Token::operator!=(const Token& rhs) const
{
	return _type != rhs._type;
}

std::ostream&	operator<<(std::ostream& os, const Token& rhs)
{
	if (rhs == Token::WORD) {
		os << *rhs._data;
		return os;
	}
	os << "'" << Token::_keys[rhs._type];
	if (rhs.isKeyWord())
		os << " keyword";
	os << "'";
	return os;
}


