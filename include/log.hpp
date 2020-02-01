#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <memory>
#include <ctime>

namespace log {

	inline std::ostream* _log_os = &std::cout;

	inline auto set_os(std::ostream* os)
	{
		_log_os = os;
	}
	
	inline auto _log() { *_log_os << std::endl; }

	template <class T, class ... Ts>
	auto _log(const T& arg, const Ts&... args) 
	{
		*_log_os << arg << " ";
		_log(args...); 
	} 

	template <class ... Ts>
	auto log(const Ts&... args)
	{
    	std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		*_log_os << "| " << now->tm_mday << "."
				 << (now->tm_mon + 1) << "."
				 << (now->tm_year + 1900) << " "
				 << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec
				 << " | ";

		_log(args...);
	}
}

#endif
