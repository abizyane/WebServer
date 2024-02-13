/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:05:34 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/13 13:07:48 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class	DeleteRequest : public IRequest{
	protected:
		std::string			_method;
		std::string			_uri;
		std::string			_version;
		std::string			_toBeDeleted;
		bool				_parseHeader(std::string &line);
		bool				_parseBody(std::string &line);
		// Response*							_response;
		// std::map<std::string, std::string>	_headers;
		

	public:
		DeleteRequest(std::string &method, std::string &uri, std::string &version);

		e_statusCode	parseRequest(std::string &request);

		~DeleteRequest( void );
};


