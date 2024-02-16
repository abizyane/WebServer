/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:05:34 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/16 12:59:01 by abizyane         ###   ########.fr       */
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
		bool								_isChunked;
		size_t								_contentLength;
		ProcessRequest&						_parse;

	public:
		DeleteRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse);

		e_statusCode	checkHeaders( void );
		e_statusCode	parseBody(std::string &line);	
		e_statusCode	parseHeader(std::string &line);

		~DeleteRequest( void );
};

#include "ProcessRequest.hpp"

