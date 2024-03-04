/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:05:34 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/04 18:35:39 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class ProcessRequest;

class	DeleteRequest : public IRequest{
	protected:
		std::string							_method;
		std::string							_uri;
		std::string							_version;
		std::map<std::string, std::string>	_headers;
		bool								_hasBody;
		size_t								_bodyIndex;
		bool								_isChunked;
		size_t								_contentLength;
		ProcessRequest&						_parse;
		std::fstream						_body;
		std::string							_fileName;

	public:
		DeleteRequest(std::string &method, std::string &uri, ProcessRequest& parse);

		e_statusCode						checkHeaders( void );
		e_statusCode						parseBody(std::string &line);
		e_statusCode						parseHeader(std::string &line);

		std::string							getMethod( void ) const;
		std::string							getUri( void ) const;
		std::map<std::string, std::string>	getHeaders( void ) const;
		std::string							getBody( void );
		ProcessRequest&						getParse( void ) const;

		~DeleteRequest( void );
};

#include "ProcessRequest.hpp"

