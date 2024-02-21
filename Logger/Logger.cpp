/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:02:08 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/02/21 16:09:29 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

Logger*	Logger::_access = nullptr;
Logger*	Logger::_error = nullptr;

Logger::Logger( const std::string& fileName ) : _fileName(fileName), _logFile(fileName.c_str(), std::ios::app)
{
}

Logger::~Logger( void ) {
	_logFile.close();
}

Logger&	Logger::getAccessLog( const std::string& accessLogStream )
{
	if (_access == nullptr)
		_access = new Logger( accessLogStream );
	return *_access;	
}

Logger&	Logger::getErrorLog( const std::string& errorLogStream )
{
	if (_error == nullptr)
		_error = new Logger( errorLogStream );
	return *_error;
}

void	Logger::_openLog( void )
{
	if (!_logFile.is_open()) {
		_logFile.open(_fileName.c_str(), std::ios::app);
	}
}

void	Logger::deleteLogs( void )
{
	delete _error;
	delete _access;
	_error = nullptr;
	_access = nullptr;
}