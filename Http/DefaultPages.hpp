/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultPages.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:29:30 by abizyane          #+#    #+#             */
/*   Updated: 2024/02/19 12:38:56 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Response.hpp"

class DefaultPages{
    private:
        // static std::string _error400;
        // static std::string _error403;
        // static std::string _error404;
        // static std::string _error405;
        // static std::string _error408;
        // static std::string _error409;
        // static std::string _error500;
        // static std::string _error501;
        // static std::string _error505;
        // static std::string _error503;
        // static std::string _generateErrorPage(int code);

    public:
        static std::string getPage(e_statusCode code);

};
