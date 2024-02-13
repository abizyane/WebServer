/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:05:34 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 23:51:34 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class ProcessRequest;
// #include "ProcessRequest.hpp"

class	DeleteRequest : public IRequest{
	protected:
		std::string							_method;
		std::string							_uri;
		std::string							_version;
		std::string							_toBeDeleted;
		std::map<std::string, std::string>	_headers;
		int									_parseHeader(std::string &line);
		int									_parseBody(std::string &line);	
		ProcessRequest&						_parse;

	public:
		DeleteRequest(std::string &method, std::string &uri, std::string &version, ProcessRequest& parse);

		e_statusCode	parseRequest(std::string &request);
		int				checkHeaders( void );

		~DeleteRequest( void );
};


