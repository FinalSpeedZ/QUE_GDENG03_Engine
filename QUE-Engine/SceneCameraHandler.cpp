#include "SceneCameraHandler.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler::SceneCameraHandler()
{
	this->sceneCamera = new Camera("SceneCamera");
}

SceneCameraHandler::~SceneCameraHandler()
{
	delete this->sceneCamera;
}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::update()
{
    this->sceneCamera->onUpdate(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::perspectiveProjection()
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	Matrix4x4 perspective;

	float degrees = 90;

	float fov = degrees * M_PI / 180.0f;

	perspective.setPerspectiveFovLH(fov, ((float)width / (float)height), 0.1f, 100.0f);

	return perspective;
}

Matrix4x4 SceneCameraHandler::orthographicProjection()
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();

	Matrix4x4 ortho;

	ortho.setOrthoLH
	(
		(rc.right - rc.left) / 300.0f,
		(rc.bottom - rc.top) / 300.0f,
		-4.0f,
		4.0f
	);

	return ortho;
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}
