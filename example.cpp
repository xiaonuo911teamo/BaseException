#include "QtGuiApplication4.h"
#include <QtWidgets/QApplication>

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

int main(int argc, char *argv[])
{
#ifndef NO_USE_STACK
	SET_DEFULTER_HANDLER();
	CBaseException be;
	be.ShowLoadModules();
	StackWalkStart();
#endif

	QApplication a(argc, argv);
	QtGuiApplication4 w;
	w.show();
	return a.exec();
}
