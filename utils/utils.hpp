/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:53:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 05:56:54 by zel-bouz         ###   ########.fr       */
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




std::string     normPath( std::string path );
unsigned long   getTime( void );
std::string     slog(const char* format, ...);
std::string     strTime( void );
time_t 			currTime( void );


template<typename T>
std::string	to_str( const T& data )
{
	std::stringstream	ss;
	ss << data;
	return ss.str();
}
