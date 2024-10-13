#include <iostream>

#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = AppWindow::getInstance();

	srand(time(0));

	while (runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	return 0;
}