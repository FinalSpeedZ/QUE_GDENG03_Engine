#include <iostream>

#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = AppWindow::getInstance();

	//runningApp->createGraphicsWindow();

	while (runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	return 0;
}