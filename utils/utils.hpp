/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:53:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/23 20:54:49 by zel-bouz         ###   ########.fr       */
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
unsigned long   getTime( void );