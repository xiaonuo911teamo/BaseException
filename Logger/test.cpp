#include "Logger/src/logger.hpp"
#include <string.h>
#include <iostream>
#include <unistd.h>

#ifndef LOG_TAG
#define LOG_TAG "logger"
#endif

Logger g_logger(std::cout);

#define LOG(__level)  g_logger << __level << __FILE__ << ":" << __LINE__ << "\t" 
#define LOGP(__level, __format, arg...)  { char msg[1024]; sprintf(msg, "%s:%d\t" __format, __FILE__, __LINE__, ##arg); g_logger << __level << msg << std::endl; }

#define LOG_DEBUG    LOG(DEBUG) // Debug message do not care in any production environment
#define LOG_INFO     LOG(INFO) // Not significant event but useful for deal with online problem
#define LOG_NOTICE   LOG(NOTICE) // Important event
#define LOG_WARN     LOG(WARN) // Important event or input which will lead to errors
#define LOG_ERROR    LOG(ERROR) // Error message means program running in an abnormal (not expected) way


int main()
{
	//Logger example(std::cout);
	//example.set_level(VERBOSE);
	//example << ERROR << "Out of Memory!" << std::endl;

	//std::stringstream ss;
	//Logger ex2(ss);
	//ex2.set_level(VERBOSE);
	//ex2 << ERROR << "aaaaaaaaa"<<std::endl;
	//ex2 << ERROR << "bbbbbbb"<<std::endl;
	//std::cout << ss.str().c_str();

	//g_logger.set_level(VERBOSE);
	//LOG_DEBUG << "aaaaa" << std::endl;
	//LOG_DEBUG << "bbb" << std::endl;
	//
	//LOGP(INFO, "%d %d", 123, 456);

	return 0;
}
