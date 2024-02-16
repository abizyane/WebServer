/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:59:15 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/16 12:58:44 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class ProcessRequest;

class	GetRequest : public IRequest{
	private:
		std::string							_method;
		std::string							_uri;
		std::string							_version;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		bool								_hasBody;
		bool								_isChunked;
		size_t								_contentLength;
		ProcessRequest&						_parse;

	public:
		GetRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse);

		e_statusCode	checkHeaders( void );
		e_statusCode	parseBody(std::string &line);
		e_statusCode	parseHeader(std::string &line);

		~GetRequest( void );
};

#include "ProcessRequest.hpp"


