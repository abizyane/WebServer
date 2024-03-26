/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:53:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/25 21:24:56 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <iostream>
#include <stdarg.h>
#include <exception>
#include <unistd.h>
#include <sys/time.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>




std::string		normPath(const std::string& path);
unsigned long   getTime( void );
std::string     slog(const char* format, ...);
std::string     strTime( void );
time_t 			currTime( void );
std::string		trim(const std::string& str);


//  ========== EXTERNAL FUNCTIONNS ==========


std::string		getFileExtension(std::string request_uri);
std::string 	generateRandomFileName(int length);
std::string 	formKey(std::string key);

template<typename T>
std::string	to_str( const T& data )
{
	std::stringstream	ss;
	ss << data;
	return ss.str();
}
