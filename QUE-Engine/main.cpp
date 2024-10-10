#include <iostream>

#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = AppWindow::getInstance();

	while (runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	return 0;
}