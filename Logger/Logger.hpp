/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:02:32 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/21 16:07:11 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#define DEFAULT_ACCESS_LOG "./logs/access"
#define DEFAULT_ERROR_LOG  "./logs/error"


#define RESET   "\033[0m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

class	Logger {
	private:
		std::stringstream	_tempBuff;
		std::string			_fileName;
		std::ofstream		_logFile;

		Logger( const std::string& fileName );
		~Logger( void );
		static Logger*	_access;
		static Logger*	_error;
		
		void	_openLog( void );


	public:
	
		template<class T>
		Logger&	operator<<( const T& data ) {
			_openLog();
			_logFile.is_open() ? _logFile << data : _tempBuff << data;
			return *this;
		}
		
		Logger&	operator<<( std::ostream& (*manip)(std::ostream&)) {
			_openLog();
			if (!_logFile.is_open())
				std::cerr << MAGENTA << "[Warning]" << RESET " : open " << _fileName << " for writing logs" << std::endl;
			
			// flush buffers
			_logFile.is_open() ? manip(_logFile) : std::cerr << _tempBuff.str() << manip;
			_tempBuff.str("");
			return *this;
		}
		
		
		static Logger&	getAccessLog( const std::string& accessLogStream = DEFAULT_ACCESS_LOG);
		static Logger&	getErrorLog( const std::string& errorLogStream = DEFAULT_ERROR_LOG );
		static void  deleteLogs( void );
};
