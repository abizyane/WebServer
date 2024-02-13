/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:59:15 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 23:51:37 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class ProcessRequest;
// #include "ProcessRequest.hpp"

class	GetRequest : public IRequest{
	private:
		std::string							_method;
		std::string							_uri;
		std::string							_version;
		std::map<std::string, std::string>	_headers;
		int									_parseHeader(std::string &line);
		int									_parseBody(std::string &line);
		ProcessRequest&						_parse;

	public:
		GetRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse);

		e_statusCode	parseRequest(std::string &request);
		int				checkHeaders( void );

		~GetRequest( void );
};


