/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConf.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:35:24 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/14 14:23:04 by nakebli          ###   ########.fr       */
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


		// to implement
		bool				hasExtention( const std::string& extention );
		std::string			getRoot( void ) const;
		std::string			getUploadStore( void ) const;
		std::string			getErrPage( int code, const std::string& defaultPage );
		bool				methodIsAllowed( const std::string& method );
		bool				dirListingEnabled( void ) const;
		size_t				getClientBodySize( void ) const;

		
		indexIter	IndexBegin( void );
		indexIter	IndexEnd( void );
};

#endif
