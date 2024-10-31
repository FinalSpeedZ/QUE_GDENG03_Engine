#include <iostream>

#include "AppWindow.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = AppWindow::getInstance();

	while (runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	GameObjectManager::destroy();
	SceneCameraHandler::destroy();

	InputSystem::destroy();
	GraphicsEngine::destroy();

	return 0;
}
