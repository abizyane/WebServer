/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:03:23 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 13:08:55 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class	PostRequest : public IRequest{
	protected:
		std::string							_method;
        std::string							_uri;
        std::string							_version;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		bool								_parseHeader(std::string &line);
		bool								_parseBody(std::string &line);
		// Response*							_response;

	public:
		PostRequest(std::string &method, std::string &uri, std::string &version);

		e_statusCode	parseRequest(std::string &request);

		~PostRequest( void );
};


