/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConf.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:35:24 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/11 12:13:53 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LocationConf_HPP_
#define _LocationConf_HPP_

#include <iostream>
#include <utility>
#include "HTTP.hpp"


class	LocationConf : public HTTP
{
	private:
		std::map<std::string, LocationConf*>	*_locations;
		std::set<std::string>					*_extentions;
		std::pair<int, std::string>				*_redirect;
		
		
		// indexIter								itbegin;
		// indexIter								itend;

		LocationConf&	operator=( const LocationConf& rhs );
	public:
		typedef std::vector<std::string>::iterator indexIter;
		LocationConf( void );
		~LocationConf( void );
		LocationConf( LocationConf const& rhs );
		LocationConf( HTTP const& rhs );

		void	addLocation( const std::string& url, LocationConf* location );
		void	addExtention( const std::string& extention );
		void	addRedirectpage( int code, const std::string& page );

		
		bool	hasRedirect( void ) const;
		bool	hasCgi( void ) const;
		bool	hasUpload( void ) const;
		bool	hasIndex( void ) const;

		
		bool				isCgi( const std::string& extention ); // .py
		std::string			getRoot( void ) const;
		std::string			getUploadStore( void ) const;
		std::string			getErrPage( int code, const std::string& defaultPage );
		bool				methodIsAllowed( const std::string& method ) const;
		bool				dirListingEnabled( void ) const; // autoIndex
		size_t				getClientBodySize( void ) const;
		std::pair<int, std::string>	getRedirectPage( void ) const;
		const std::vector<std::string>&	getIndex( void ) const;

		// return 301 facebook.com/home

		void	passDirectiveToRoutes( void );
		LocationConf*	getUri( std::string uri ) const;
};

#endif
