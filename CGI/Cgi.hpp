/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:37:01 by nakebli           #+#    #+#             */
/*   Updated: 2024/03/15 06:17:45 by nakebli          ###   ########.fr       */
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
        std::string     _file_path;
        std::string     _query_string;
        char**          _cgi_argv;
        ProcessRequest* _processor;
        Selector*       _selector;
        pid_t           pid;
        
        void    setArguments( void );

    public:
        std::string     _cgiRespo_fileName;
        Cgi( ProcessRequest* processor, Selector *selector );
        ~Cgi( void );

        void            init();
        void            execute( int& fd );
        int             addHeaders( void );
        void            printfile( void );
        // std::string     readFile( void );
};
