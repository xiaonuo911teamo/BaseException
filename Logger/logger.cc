/*
 * logger.cc
 *
 *
 * Logger Library
 *
 *
 * Copyright (C) 2013-2017  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#include "logger.hpp"

#ifdef __ANDROID__
#define LOG_TAG "logger"
#include <android/log.h>
#endif

Logger::Logger(std::ostream& s) : _file(), 
				_log(s),
				_level(logger_level::LL_INFO),
				_line_level(logger_level::LL_VERBOSE),
				_default_line_level(logger_level::LL_VERBOSE)
#ifdef PIPELINE_LOG_THREAD_SAFE
				, _spinlock()
#endif
{
	atomic_flag_clear(&_spinlock); // ATOMIC_FLAG_INIT
}


Logger::Logger(const char *f) : _file(f, std::ios::out | std::ios::app), 
				_log(_file),
				_level(logger_level::LL_INFO),
				_line_level(logger_level::LL_VERBOSE),
				_default_line_level(logger_level::LL_VERBOSE)
{
    assert(_file.is_open());
}


Logger::Logger(const std::string& f) : _file(f.c_str(), std::ios::out | std::ios::app), 
				       _log(_file),
					   _level(logger_level::LL_INFO),
					   _line_level(logger_level::LL_VERBOSE),
					   _default_line_level(logger_level::LL_VERBOSE)
{
    assert(_file.is_open());
}


Logger::~Logger()
{
    if (_file.is_open()) {
	_log.flush();
	_file.close();
    }
	else {
		_log.flush();
	}
}


void Logger::set_level(const logger_level::_logger_level level)
{
    _level = level;
}  


void Logger::set_default_line_level(const logger_level::_logger_level level)
{
    _default_line_level = level;
}


void Logger::flush()
{
    if (_line_level >= _level) {
		_log << get_time() << " -- [" << level_str(_line_level) << "] -- " << str();
#ifdef __ANDROID__
        std::stringstream& _log_ss(static_cast<std::stringstream&>(_log));
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "%s", _log_ss.str().c_str());//#todo level convert
        _log_ss.str("");
#endif
		if (_file.is_open())
			_log.flush();
    }
    
    str("");
    _line_level = _default_line_level;

#ifdef PIPELINE_LOG_THREAD_SAFE
	_spinlock.clear(std::memory_order_relaxed); // std::memory_order_release
#endif
}


Logger& Logger::operator<<(const logger_level::_logger_level level)
{
#ifdef PIPELINE_LOG_THREAD_SAFE
	// see: https://github.com/lattera/glibc/blob/master/mach/spin-solid.c
	// see: http://www.cnblogs.com/haippy/p/3252056.html
	// see: https://zh.cppreference.com/w/cpp/atomic/memory_order
	while (_spinlock.test_and_set(std::memory_order_relaxed)); // std::memory_order_acquire
#endif

    _line_level = level;
    return (*this);
}


Logger& Logger::operator<<(LoggerManip m)
{ 
    return m(*this);
}


std::string Logger::get_time() const
{
	struct tm *timeinfo;
	time_t rawtime;
	char *time_buf;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	time_buf = asctime(timeinfo);

	std::string ret(time_buf);
	if (!ret.empty() && ret[ret.length() - 1] == '\n') {
		ret.erase(ret.length() - 1);
	}

	return (ret);
}


inline const char* Logger::level_str(const logger_level::_logger_level level)
{
    switch (level) {
	case logger_level::LL_VERBOSE: return ("VRB");
	case logger_level::LL_DEBUG: return ("DBG");
	case logger_level::LL_INFO: return ("INF");
	case logger_level::LL_NOTICE: return ("NOT");
	case logger_level::LL_WARNING: return ("WRN");
	case logger_level::LL_ERROR: return ("ERR");
	case logger_level::LL_CRITICAL: return ("CRT");
    default:
		assert(false);
		return nullptr;
    }
}
