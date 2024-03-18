/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:23 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/18 18:19:47 by abizyane         ###   ########.fr       */
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
		std::fstream						_body;
		std::string							_fileName;
		size_t								_bodyIndex;
		bool								_isChunked;
		size_t								_chunkLen;
		bool								_gotChunkLen;
		size_t								_contentLength;
		ProcessRequest&						_parse;

	public:
		PostRequest(std::string &method, std::string &uri, ProcessRequest& parse);

		e_statusCode						checkHeaders( void );
		e_statusCode						parseBody(std::string &line);
		e_statusCode						parseHeader(std::string &line);

		std::string							getMethod( void ) const;
		std::string							getUri( void ) const;
		std::map<std::string, std::string>	getHeaders( void ) const;
		std::vector<char>					getBody( void );
		ProcessRequest&						getParse( void ) const;

		~PostRequest( void );
};

#include "ProcessRequest.hpp"
