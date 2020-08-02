#include "logger.h"
#ifndef NO_USE_STACK
#include "Crash/BaseException.h"
#endif

#ifndef NO_USE_STACK
void StackWalkStart()
{
	CBaseException sw;
	sw.ShowCallstack();
}
#endif

Logger g_logger("log.txt");

int main()
{
#ifndef NO_USE_STACK
	SET_DEFULTER_HANDLER();
	CBaseException be;
	be.ShowLoadModules();
	StackWalkStart();
#endif

	int div = 0;
	for (int i = 0; i < 10; i++)
		div = 10 / i;

	return 0;
}