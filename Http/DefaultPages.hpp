/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultPages.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:29:30 by abizyane          #+#    #+#             */
/*   Updated: 2024/03/11 12:05:23 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Response.hpp"

class DefaultPages{
    private:
        static std::map<int, std::string> _errorPages;

    public:
        static std::string getPage(e_statusCode code);
};

std::map<int, std::string>  init_pages( void );