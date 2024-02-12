/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:05:34 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/12 23:15:25 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRequest.hpp"

class	DeleteRequest : public IRequest{
	protected:
		std::string							_method;
		std::string							_uri;
		std::string							_version;
		std::string							_toBeDeleted;
		// Response*							_response;
		// std::map<std::string, std::string>	_headers;
		

	public:
		DeleteRequest(std::string &method, std::string &uri, std::string &version);

		e_statuscode	parseRequest(std::__1::string &request);
		bool			parseHeader(std::__1::string &line);
		bool			parseBody(std::__1::string &line);

		~DeleteRequest( void );
};


