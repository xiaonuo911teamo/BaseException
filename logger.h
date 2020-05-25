#ifndef __PL_LOGGER__
#define __PL_LOGGER__

#define LOG_ENDL     std::endl

//#define PIPELINE_LOG_DUMMY

#ifndef PIPELINE_LOG_DUMMY

#include "Logger/logger.hpp"
#include <string.h>

extern Logger g_logger;

#define LOG(__level)  g_logger << __level << __FILE__ << ":" << __LINE__ << "\t"
#ifdef _WIN32
#define LOGP(__level, __format, ...)  { char msg[1024]; sprintfse(msg, "%s:%d\t" __format, __FILE__, __LINE__, __VA_ARGS__); g_logger << __level << msg << LOG_ENDL; }
#else
#define LOGP(__level, __format, args...)  { char msg[1024]; sprintfse(msg, "%s:%d\t" __format, __FILE__, __LINE__, ##args); g_logger << __level << msg << LOG_ENDL; }
#endif

#else // PIPELINE_LOG_DUMMY

#include <iostream>
#include <string.h>
#include <unistd.h>

#define LOG(__level)  std::cout << __level << __FILE__ << ":" << __LINE__ << "\t"
#ifdef _WIN32
#define LOGP(__level, __format, ...)  { char msg[1024]; sprintfse(msg, "%s:%d\t" __format, __FILE__, __LINE__, __VA_ARGS__); std::cout << __level << msg << LOG_ENDL; }
#else
#define LOGP(__level, __format, args...)  { char msg[1024]; sprintfse(msg, "%s:%d\t" __format, __FILE__, __LINE__, ##args); std::cout << __level << msg << LOG_ENDL; }
#endif

#endif

#define PLDEBUG    logger_level::LL_DEBUG
#define PLINFO     logger_level::LL_INFO
#define PLNOTICE   logger_level::LL_NOTICE
#define PLWARNING  logger_level::LL_WARNING
#define PLERROR    logger_level::LL_ERROR

#define LOG_DEBUG    LOG(PLDEBUG) // Debug message do not care in any production environment
#define LOG_INFO     LOG(PLINFO) // Not significant event but useful for deal with online problem
#define LOG_NOTICE   LOG(PLNOTICE) // Important event
#define LOG_WARN     LOG(PLWARNING) // Important event or input which will lead to errors
#define LOG_ERROR    LOG(PLERROR) // Error message means program running in an abnormal (not expected) way

#ifndef NO_USE_STACK
#define LOG_NO_PATH(__level)  g_logger << __level << "\t"
#define LOG_EXCEPTION LOG_NO_PATH(PLERROR)
#endif

#endif

