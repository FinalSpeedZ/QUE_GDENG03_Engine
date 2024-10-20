#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"

Camera::Camera()
	: GameObject("Camera")
{
	worldCam.setTranslation(Vector3D(0, 0, -2));
}

Camera::Camera(std::string name)
	: GameObject(name)
{
}

void Camera::onCreate()
{
	GameObject::onCreate();
}

void Camera::onUpdate(float deltatime)
{
	GameObject::onUpdate(deltatime);

	updateMatrix();
}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}

void Camera::updateMatrix()
{
	constant cc;

	Matrix4x4 temp;

	cc.m_world.setIdentity();

	Matrix4x4 tempworldCam;
	tempworldCam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(localRotation.x);
	tempworldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y);
	tempworldCam *= temp;

	Vector3D newPos = worldCam.getTranslation() + tempworldCam.getZDirection() * (forward * 0.3f);
	newPos = newPos + tempworldCam.getXDirection() * (rightward * 0.3f);

	tempworldCam.setTranslation(newPos);

	worldCam = tempworldCam;

	tempworldCam.inverse();

	cc.m_view = tempworldCam;

	//cc.m_projection = getOrthoMatrix();
	cc.m_projection = getPersMatrix();

	worldViewProj = cc;
}

Matrix4x4 Camera::getOrthoMatrix()
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

Matrix4x4 Camera::getPersMatrix()
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

constant Camera::getUpdatedConstantData()
{
	return worldViewProj;
}
