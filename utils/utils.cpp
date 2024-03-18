/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:51:28 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/18 21:41:29 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"
#include <stack>

/*
	""						=> "/"
	"//"					=> "/"
	"//home/../blog/"		=> "/blog"
	"/home/"				=> "/home"
	"./home"				=> "/home"
	"../home/"				=> "/home"
	"/home/../../../blog/"	=> "/blog"
*/

std::string normPath(const std::string& path) {
	std::string result;
	std::stack<std::string> s;
	s.push("/");

	for (size_t i = 0; i < path.size(); ++i) {
		if (path[i] == '/') {
			if ((!s.empty() && s.top() == "/") || i + 1 == path.size())
				continue;
			else
				s.push("/");
		} else if (path[i] == '.') {
			if (i + 1 < path.size() && path[i + 1] == '.') {
				if (s.size() > 1) // Avoid popping the root "/"
					s.pop();
				i++;
			}
		} else {
			std::string dir;
			while (i < path.size() && path[i] != '/') {
				dir += path[i];
				i++;
			}
			s.push(dir);
			--i;
		}
	}

	while (!s.empty()) {
		result = s.top() + result;
		s.pop();
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
