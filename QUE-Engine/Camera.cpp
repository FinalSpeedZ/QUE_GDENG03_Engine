#include "Camera.h"

#include "AppWindow.h"

Camera::Camera()
	: GameObject("Camera")
{
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
	Matrix4x4 temp;

	cc.m_world.setIdentity();

	Matrix4x4 worldCam;
	worldCam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y);
	worldCam *= temp;

	worldCam.setTranslation(Vector3D(0, 0, -2));

	worldCam.inverse();

	RECT rc = AppWindow::getInstance()->getClientWindowRect();

	cc.m_view = worldCam;

	cc.m_projection.setOrthoLH
	(
		(rc.right - rc.left) / 300.0f,
		(rc.bottom - rc.top) / 300.0f,
		-4.0f,
		4.0f
	);
}

constant Camera::getUpdatedConstantData()
{
	return cc;
}
