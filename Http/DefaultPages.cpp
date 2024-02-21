/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultPages.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:28:56 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/20 20:57:57 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DefaultPages.hpp"


std::string DefaultPages::getPage(e_statusCode code){
    switch (code){
        case HTTP_BAD_REQUEST:
            return "<!DOCTYPE html>\n<html>\n<head>\n<title>400 Bad Request</title>\n</head>\n<body>\n<h1>400 Bad Request</h1>\n<p>Your browser sent a request that this server could not understand.</p>\n</body>\n</html>";
        case HTTP_FORBIDDEN:
            return "<!DOCTYPE html>\n<html>\n<head>\n<title>403 Forbidden</title>\n</head>\n<body>\n<h1>403 Forbidden</h1>\n<p>You don't have permission to access this resource.</p>\n</body>\n</html>";
        case HTTP_NOT_FOUND:
            return "<!DOCTYPE html>\n<html>\n<head>\n<title>404 Not Found</title>\n</head>\n<body>\n<h1>404 Not Found</h1>\n<p>The requested URL was not found on this server.</p>\n</body>\n</html>";
        default:
            return "<!DOCTYPE html>\n<html>\n<head>\n<title>500 Internal Server Error</title>\n</head>\n<body>\n<h1>500 Internal Server Error</h1>\n<p>The server encountered an internal error and was unable to complete your request.</p>\n</body>\n</html>";
    }
    return "";
};

// std::string DefaultPages::_generateErrorPage(int code){
    
// }