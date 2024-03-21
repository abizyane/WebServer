/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultPages.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:28:56 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/11 11:53:38 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DefaultPages.hpp"

std::map<int, std::string> DefaultPages::_errorPages = init_pages();

std::map<int, std::string>  init_pages( void )
{
    std::map<int, std::string> _errorPages;
    _errorPages[HTTP_BAD_REQUEST] = "<html><head><title>400 Bad Request</title></head><body bgcolor=\"white\"><center><h1>400 Bad Request</h1></center><hr><center>HTTP Error 400: Bad Request</center></body></html>";
    _errorPages[HTTP_UNAUTHORIZED] = "<html><head><title>401 Unauthorized</title></head><body bgcolor=\"white\"><center><h1>401 Unauthorized</h1></center><hr><center>HTTP Error 401: Unauthorized</center></body></html>";
    _errorPages[HTTP_PAYMENT_REQUIRED] = "<html><head><title>402 Payment Required</title></head><body bgcolor=\"white\"><center><h1>402 Payment Required</h1></center><hr><center>HTTP Error 402: Payment Required</center></body></html>";
    _errorPages[HTTP_FORBIDDEN] = "<html><head><title>403 Forbidden</title></head><body bgcolor=\"white\"><center><h1>403 Forbidden</h1></center><hr><center>HTTP Error 403: Forbidden</center></body></html>";
    _errorPages[HTTP_NOT_FOUND] = "<html><head><title>404 Not Found</title></head><body bgcolor=\"white\"><center><h1>404 Not Found</h1></center><hr><center>HTTP Error 404: Not Found</center></body></html>";
    _errorPages[HTTP_METHOD_NOT_ALLOWED] = "<html><head><title>405 Method Not Allowed</title></head><body bgcolor=\"white\"><center><h1>405 Method Not Allowed</h1></center><hr><center>HTTP Error 405: Method Not Allowed</center></body></html>";
    _errorPages[HTTP_NOT_ACCEPTABLE] = "<html><head><title>406 Not Acceptable</title></head><body bgcolor=\"white\"><center><h1>406 Not Acceptable</h1></center><hr><center>HTTP Error 406: Not Acceptable</center></body></html>";
    _errorPages[HTTP_PROXY_AUTHENTICATION_REQUIRED] = "<html><head><title>407 Proxy Authentication Required</title></head><body bgcolor=\"white\"><center><h1>407 Proxy Authentication Required</h1></center><hr><center>HTTP Error 407: Proxy Authentication Required</center></body></html>";
    _errorPages[HTTP_REQUEST_TIMEOUT] = "<html><head><title>408 Request Timeout</title></head><body bgcolor=\"white\"><center><h1>408 Request Timeout</h1></center><hr><center>HTTP Error 408: Request Timeout</center></body></html>";
    _errorPages[HTTP_CONFLICT] = "<html><head><title>409 Conflict</title></head><body bgcolor=\"white\"><center><h1>409 Conflict</h1></center><hr><center>HTTP Error 409: Conflict</center></body></html>";
    _errorPages[HTTP_GONE] = "<html><head><title>410 Gone</title></head><body bgcolor=\"white\"><center><h1>410 Gone</h1></center><hr><center>HTTP Error 410: Gone</center></body></html>";
    _errorPages[HTTP_LENGTH_REQUIRED] = "<html><head><title>411 Length Required</title></head><body bgcolor=\"white\"><center><h1>411 Length Required</h1></center><hr><center>HTTP Error 411: Length Required</center></body></html>";
    _errorPages[HTTP_PRECONDITION_FAILED] = "<html><head><title>412 Precondition Failed</title></head><body bgcolor=\"white\"><center><h1>412 Precondition Failed</h1></center><hr><center>HTTP Error 412: Precondition Failed</center></body></html>";
    _errorPages[HTTP_REQUEST_ENTITY_TOO_LARGE] = "<html><head><title>413 Request Entity Too Large</title></head><body bgcolor=\"white\"><center><h1>413 Request Entity Too Large</h1></center><hr><center>HTTP Error 413: Request Entity Too Large</center></body></html>";
    _errorPages[HTTP_REQUEST_URI_TOO_LONG] = "<html><head><title>414 Request-URI Too Long</title></head><body bgcolor=\"white\"><center><h1>414 Request-URI Too Long</h1></center><hr><center>HTTP Error 414: Request-URI Too Long</center></body></html>";
    _errorPages[HTTP_UNSUPPORTED_MEDIA_TYPE] = "<html><head><title>415 Unsupported Media Type</title></head><body bgcolor=\"white\"><center><h1>415 Unsupported Media Type</h1></center><hr><center>HTTP Error 415: Unsupported Media Type</center></body></html>";
    _errorPages[HTTP_REQUESTED_RANGE_NOT_SATISFIABLE] = "<html><head><title>416 Requested Range Not Satisfiable</title></head><body bgcolor=\"white\"><center><h1>416 Requested Range Not Satisfiable</h1></center><hr><center>HTTP Error 416: Requested Range Not Satisfiable</center></body></html>";
    _errorPages[HTTP_EXPECTATION_FAILED] = "<html><head><title>417 Expectation Failed</title></head><body bgcolor=\"white\"><center><h1>417 Expectation Failed</h1></center><hr><center>HTTP Error 417: Expectation Failed</center></body></html>";
    _errorPages[HTTP_INTERNAL_SERVER_ERROR] = "<html><head><title>500 Internal Server Error</title></head><body bgcolor=\"white\"><center><h1>500 Internal Server Error</h1></center><hr><center>HTTP Error 500: Internal Server Error</center></body></html>";
    _errorPages[HTTP_NOT_IMPLEMENTED] = "<html><head><title>501 Not Implemented</title></head><body bgcolor=\"white\"><center><h1>501 Not Implemented</h1></center><hr><center>HTTP Error 501: Not Implemented</center></body></html>";
    _errorPages[HTTP_BAD_GATEWAY] = "<html><head><title>502 Bad Gateway</title></head><body bgcolor=\"white\"><center><h1>502 Bad Gateway</h1></center><hr><center>HTTP Error 502: Bad Gateway</center></body></html>";
    _errorPages[HTTP_SERVICE_UNAVAILABLE] = "<html><head><title>503 Service Unavailable</title></head><body bgcolor=\"white\"><center><h1>503 Service Unavailable</h1></center><hr><center>HTTP Error 503: Service Unavailable</center></body></html>";
    _errorPages[HTTP_GATEWAY_TIMEOUT] = "<html><head><title>504 Gateway Timeout</title></head><body bgcolor=\"white\"><center><h1>504 Gateway Timeout</h1></center><hr><center>HTTP Error 504: Gateway Timeout</center></body></html>";
    _errorPages[HTTP_VERSION_NOT_SUPPORTED] = "<html><head><title>505 HTTP Version Not Supported</title></head><body bgcolor=\"white\"><center><h1>505 HTTP Version Not Supported</h1></center><hr><center>HTTP Error 505: HTTP Version Not Supported</center></body></html>";
    return _errorPages;
}
std::string DefaultPages::getPage(e_statusCode code)
{
    return _errorPages[code];
}


