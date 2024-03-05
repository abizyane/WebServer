/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:53:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/05 14:26:04 by nakebli          ###   ########.fr       */
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
#include <sys/time.h>
#include <sys/stat.h>

enum PathType { UNKNOWN, FILE_PATH, DIRECTORY_PATH };

template<typename T>
char * str(const T& data) {
    std::stringstream   ss;
    ss << std::boolalpha;
    ss << data;
    return strdup(ss.str().c_str());
}

template<typename T>
std::string toString(const T& data) {
    std::stringstream   ss;
    ss << std::boolalpha;
    ss << data;
    return ss.str();
}


void    error(int n, ...);
std::string    normPath( std::string path );
PathType get_resource_type(const std::string& path);
unsigned long   getTime( void );