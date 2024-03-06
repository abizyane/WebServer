/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:51:28 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/06 05:56:43 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"


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

std::string slog(const char* format, ...)
{
    std::string result;
    va_list		args;

    va_start(args, format);
    for (size_t i = 0; format[i]; i++) {
        if (format[i] == '%' && strchr("sdf", format[i + 1])) {
            switch (format[++i]) {
                case 's': result.append(va_arg(args, const char*)); break;
                case 'd': result.append(to_str(va_arg(args, int))); break;
                case 'f': result.append(to_str(va_arg(args, double))); break;
                default: break;
            }
        } else {
            result += format[i];
        }
    }
    return va_end(args), result;
}


std::string	strTime()
{
    std::time_t currentTime;
    std::tm* localTime;
    char buffer[80];

    std::time(&currentTime);
    localTime = std::localtime(&currentTime);
    std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d-%H:%M:%S]", localTime);
    return std::string(buffer);
}


time_t  currTime( void ) 
{
    time_t ans = time(NULL);
    return ans;
}