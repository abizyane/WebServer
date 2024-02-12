/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:07:21 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 14:57:33 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

std::map<std::string, Token::token>	initKeywords( void ) {
	std::map<std::string, Token::token>	keywords;

	Token::token	toks[] = {
		Token::HTTP, Token::SERVER, Token::LOCATION, Token::HOST, Token::PORT, 
		Token::ROOT, Token::ALLOW, Token::DENY, Token::INDEX, Token::AUTO, Token::ERR_PAGE,
		Token::BODY_SIZE, Token::UPLOAD, Token::CGI, Token::RETURN,
	};

	std::string		keys[] = {
		"http", "server", "location", "host", "port", "root", "allow", "deny",
		"index", "autoindex", "error_page", "client_body_max_size", "upload_store",
		"cgi", "return",
	};

	const int N = sizeof(toks) / sizeof(toks[0]);
	for (int i = 0; i < N; i++) {
		keywords[keys[i]] = toks[i];
	}
	return keywords;
}


Lexer::Lexer( const std::string& filePath ) : _line(1)
{
	std::ifstream	file(filePath.c_str());
	if (!file.is_open())
		throw std::runtime_error((filePath + " can't be opened").c_str());
	if (!std::getline(file, _data, '\0'))
		throw std::runtime_error((filePath + " is empty").c_str());
	_curr = _data[(_pos = 0)];
}

Lexer::~Lexer( void )
{
}

void	Lexer::_advance( void )
{
	_line += (_curr == '\n');
	if (_curr != '\0') {
		_curr = _data[++_pos];
	}
}

void	Lexer::_skipComment( void ) 
{
	while (_curr != '\n')
		_advance();		
}

Token	Lexer::_parseWord( void )
{
	std::string	result;
	while (!strchr("\n\r\f\t\v {};", _curr)) {
		result += _curr;
		_advance();
	}
	std::map<std::string, Token::token>::iterator res = _keywords.find(result);
	if (res != _keywords.end())
		return res->second;
	return result;
}

Token	Lexer::getNextToken( void )
{
	while (_curr != '\0') {
		if (isspace(_curr)) {
			_advance();
			continue;
		}
		switch (_curr) {
			case '{':	_advance(); return Token::OPEN_CURLY;
			case '}':	_advance(); return Token::CLOSE_CURLY;
			case ';':	_advance(); return Token::SEMICOLEN;
			case '#':	_skipComment(); break;
			default:	return _parseWord();
		}
	}
	return Token::_EOF;
}