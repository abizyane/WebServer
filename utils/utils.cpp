/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:51:28 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/13 10:16:51 by zel-bouz         ###   ########.fr       */
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






