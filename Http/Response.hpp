/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:07:10 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/01 16:39:47 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ProcessRequest.hpp"
#include "../Configuration/MainConf.hpp"
#include "../Configuration/LocationConf.hpp"
#include "DefaultPages.hpp"

typedef enum {
	ERROR,
	RESPONSE,
	BODY,
	DONE
} e_state;

class Response {
	private :
		IRequest*							_request;
		ProcessRequest*						_parse;
		LocationConf*						_location;
		bool								_good;
		e_statusCode						_status;
		e_state								_state;
		size_t								_bodyIndex;
		std::string							_response;
		std::map<std::string, std::string>  _headers;
		std::vector<char>					_body;
		
		void								_buildResponse( void );
		void								_processGetResponse( void );
		void								_processPostResponse( void );
		void								_processDeleteResponse( void );
		void								_prepareResponse( void );
	
	public :
		Response(IRequest& request, ProcessRequest& parse, int port);

		bool			good( void );

		std::string		GetResponse(void);
		~Response();

};

		// std::string& 						GetResponse(void);
		// size_t		 						GetLength(void);
		// std::string& 						GetBody(void);
		// std::string& 						GetContentType(void);
		// e_statusCode 						GetStatusCode(void);
		// std::map<std::string, std::string>& GetHeaders(void);
		// std::string& 						GetHeader(const std::string& key);

		// typedef enum {
    	// Continue = 100,
        // Switching_Protocols = 101,
        // OK = 200,
        // Created = 201,
        // Accepted = 202,
        // Non_Authoritative_Information = 203,
        // No_Content = 204,
        // Reset_Content = 205,
        // Partial_Content = 206,
        // Multiple_Choices = 300,
        // Moved_Permanently = 301,
        // Found = 302,
        // See_Other = 303,
        // Not_Modified = 304,
        // Use_Proxy = 305,
        // Temporary_Redirect = 307,
        // Bad_Request = 400,
        // Unauthorized = 401,
        // Payment_Required = 402,
        // Forbidden = 403,
        // Not_Found = 404,
        // Method_Not_Allowed = 405,
        // Not_Acceptable = 406,
        // Proxy_Authentication_Required = 407,
        // Request_Time_out = 408,
        // Conflict = 409,
        // Gone = 410,
        // Length_Required = 411,
        // Precondition_Failed = 412,
        // Request_Entity_Too_Large = 413,
        // Request_URI_Too_Large = 414,
        // Unsupported_Media_Type = 415,
        // Requested_range_not_satisfiable = 416,
        // Expectation_Failed = 417,
        // Internal_Server_Error = 500,
        // Not_Implemented = 501,
        // Bad_Gateway = 502,
        // Service_Unavailable = 503,
        // Gateway_Time_out = 504,
        // HTTP_Version_not_supported = 505
		// } e_statusCode;
		