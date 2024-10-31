#pragma once

#include <vector>

#include "Camera.h"
#include "Matrix4x4.h"

class SceneCameraHandler
{
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator= (SceneCameraHandler const&) {};

	static SceneCameraHandler* sharedInstance;

public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	static Matrix4x4 perspectiveProjection();
	static Matrix4x4 orthographicProjection();

	Camera* getActiveCamera();

private:
	std::vector<Camera*> cameras;
};

