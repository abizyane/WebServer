/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:23 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/18 12:19:47 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class ProcessRequest;

class	PostRequest : public IRequest{
	protected:
		std::string							_method;
        std::string							_uri;
        std::string							_version;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		size_t								_bodyIndex;
		bool								_isChunked;
		size_t								_contentLength;
		ProcessRequest&						_parse;


	public:
		PostRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse);

		e_statusCode	checkHeaders( void );
		e_statusCode	parseBody(std::string &line);
		e_statusCode	parseHeader(std::string &line);

		std::string			getMethod( void ) const;
		std::string			getUri( void ) const;
		std::map<std::string, std::string>	getHeaders( void ) const;
		std::string			getBody( void ) const;
		ProcessRequest&		getParse( void ) const;

		~PostRequest( void );
};

#include "ProcessRequest.hpp"
