/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:37:01 by nakebli           #+#    #+#             */
/*   Updated: 2024/03/11 09:18:11 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Configuration/ServerConf.hpp"
#include "../Http/ProcessRequest.hpp"
#include "../Http/GetRequest.hpp"
#include "../Http/PostRequest.hpp"
#include "../Http/DeleteRequest.hpp"
#include "../Core/Selector.hpp"
#include "../utils/utils.hpp"
#include <fcntl.h>

class Cgi
{
    private:
        std::string     _body_file;
        char**          _cgi_argv;
        ProcessRequest* _processor;
        Selector*       _selector;
        pid_t           pid;
        
        void    setArguments( void );

    public:
        std::string     _cgiRespo_fileName;
        Cgi( ProcessRequest* processor, Selector *selector );
        ~Cgi( void );

        void    init();
        void    execute( int& fd );
        // std::string    readFile( void );
};
