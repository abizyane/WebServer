/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConf.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:35:24 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/12 11:58:32 by zel-bouz         ###   ########.fr       */
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
		LocationConf( void );
		~LocationConf( void );
		LocationConf( LocationConf const& rhs );

		void	addLocation( const std::string& url, LocationConf* location );
		void	addExtention( const std::string& extention );
		void	addRedirectpage( int code, const std::string& page );
		bool	hasRedirect( void ) const;
		bool	cgiIsAllowed( void ) const;
};

#endif
