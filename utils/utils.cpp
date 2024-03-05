/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:51:28 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/05 14:25:38 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"


void    error(int n, ...) {
    va_list args;
    std::stringstream   ss;
    va_start(args, n);
    while (n--) {
        char *s = va_arg(args, char*);
        ss << s;
        free(s);
    }
    throw std::runtime_error(ss.str().c_str());
}

std::string    normPath( std::string path )
{
    std::string result;
    bool previousSlash = false;
    std::string::iterator   it = path.begin();

    for (; it != path.end(); it++) {
        if (*it == '/') {
            if (!previousSlash) {
                result += *it;
            }
            previousSlash = true;
            continue ;
        }
        result += *it;
        previousSlash = false;
    }
    return result;
}

unsigned long   getTime( void )
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec;
}

PathType get_resource_type(const std::string& path) {
    struct stat fileInfo;
    if (stat(path.c_str(), &fileInfo) != 0)
        return UNKNOWN; // Error occurred, cannot determine type

    if (S_ISREG(fileInfo.st_mode))
        return FILE_PATH; // Regular file
    else if (S_ISDIR(fileInfo.st_mode))
        return DIRECTORY_PATH; // Directory
    else
        return UNKNOWN; // Neither regular file nor directory
}