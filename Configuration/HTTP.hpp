/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:35:28 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/14 10:28:08 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HTTP_HPP_
#define _HTTP_HPP_

#include <iostream>
#include <set>
#include <map>
#include <vector>

class	HTTP
{
	private:
		std::string					*_root;
		std::map<int, std::string>	*_errorPage; // TODO: make the value as vector of strings
		std::set<std::string>		*_allowed;
		std::vector<std::string>	*_index;
		std::string					*_uploadStore;
		bool						_autoIndex;
		size_t						_clientMaxBody;
		std::set<std::string>		_setDirectives;

	public:
		HTTP( void );
		~HTTP( void );
		HTTP( HTTP const& rhs );
		HTTP&	operator=( const HTTP& rhs );
		
		void	allowMethod( const std::string& method );
		void	denyMethod( const std::string& method );
		void	setRoot( const std::string& root );
		void	setUploadStore( const std::string& uploadSotore );
		void	addIndex( const std::string& index );
		void	setAutoIndex( bool autoIndex );
		void	addErrorPage( int code, const std::string& page );
		void	setClientBody( size_t size );

		void	markDirective( const std::string& directiveName );
		bool	hasDirective( const std::string& directiveName );
};

#endif
