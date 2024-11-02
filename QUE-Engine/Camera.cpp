#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

Camera::Camera(std::string name)
	: GameObject(name)
{
	localPosition.z = -5.0;

	this->updateViewMatrix();

	this->projection = SceneCameraHandler::perspectiveProjection();

	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::onCreate()
{
	GameObject::onCreate();
}

void Camera::onUpdate(float deltatime)
{
	GameObject::onUpdate(deltatime);

	float moveSpeed = 10.0f;

	float x = localPosition.x;
	float y = localPosition.y;
	float z = localPosition.z;

	Vector3D newPosition = localPosition;

	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		newPosition = newPosition + this->localMatrix.getZDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		newPosition = newPosition - this->localMatrix.getZDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		newPosition = newPosition - this->localMatrix.getXDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		newPosition = newPosition + this->localMatrix.getXDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('Q'))
	{
		newPosition = newPosition + this->localMatrix.getYDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('E'))
	{
		newPosition = newPosition - this->localMatrix.getYDirection() * (moveSpeed * deltatime);
	}

	if (newPosition != localPosition)
	{
		setPosition(newPosition.x, newPosition.y, newPosition.z);
		this->updateViewMatrix();
	}

}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();

	temp.setIdentity();
	temp.setScale(localScale);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationX(localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationZ(localRotation.z);
	worldCam *= temp;

	temp.setTranslation(localPosition);
	worldCam *= temp;

	worldCam = worldCam.inverse();

	this->localMatrix = worldCam;
}

Ray Camera::screenToWorldRay(const Vector2D& screenPos)
{
	// Get the dimensions of the viewport
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	POINT clientPos = { static_cast<LONG>(screenPos.x), static_cast<LONG>(screenPos.y) };
	HWND hwnd = AppWindow::getInstance()->getHWND();
	ScreenToClient(hwnd, &clientPos);

	//std::cout << clientPos.x << ", " << clientPos.y << std::endl;

	// Convert screen coordinates to normalized device coordinates (NDC)
	float xNDC = (2.0f * clientPos.x) / width - 1.0f; // x in [-1, 1]
	float yNDC = 1.0f - (2.0f * clientPos.y) / height; // y in [-1, 1]

	// Create the clip space position
	Vector4D clipSpacePos(xNDC, yNDC, -1.0f, 1.0f);

	// Get the inverse projection matrix and view matrix
	Matrix4x4 invProj = this->projection.inverse(); // Inverse of projection matrix

	//std::cout << "Projection Matrix\n";
	//this->projection.print();

	//std::cout << "Projection Matrix Inverse\n";
	//invProj.print();

	// Transform to view space
	Vector4D viewSpacePos = invProj * clipSpacePos;
	Vector3D zDirection = this->localMatrix.getZDirection();
	// Normalize the direction
	zDirection = zDirection.normalize();

	// Clamp small values
	const float epsilon = 0.0001f;
	if (fabs(zDirection.x) < epsilon) zDirection.x = 0.0f;
	if (fabs(zDirection.y) < epsilon) zDirection.y = 0.0f;
	if (fabs(zDirection.z) < epsilon) zDirection.z = 0.0f;

	if (fabs(zDirection.x) > fabs(zDirection.y) && fabs(zDirection.x) > fabs(zDirection.z)) 
	{
		viewSpacePos.x = 1.0f;
		//std::cout << "Facing X Axis" << std::endl;
	}
	else if (fabs(zDirection.y) > fabs(zDirection.x) && fabs(zDirection.y) > fabs(zDirection.z)) 
	{
		viewSpacePos.y = 1.0f;
		//std::cout << "Facing Y Axis" << std::endl;
	}
	else if (fabs(zDirection.z) > fabs(zDirection.x) && fabs(zDirection.z) > fabs(zDirection.y)) 
	{
		viewSpacePos.z = 1.0f;
		//std::cout << "Facing Z Axis" << std::endl;
	}
	viewSpacePos.w = 0.0f;

	//std::cout << zDirection.x << ", " << zDirection.y << ", " << zDirection.z << std::endl;

	// Transform to world space
	this->localMatrix.setZDirection(zDirection);

	//this->localMatrix.print();

	Matrix4x4 invView = this->localMatrix.inverse(); // Inverse of view matrix
	Vector4D worldSpacePos = invView * viewSpacePos;

	// The direction of the ray
	Vector3D rayDirection(worldSpacePos.x, worldSpacePos.y, worldSpacePos.z);
	rayDirection = rayDirection.normalize(); // Ensure direction is normalized

	Vector3D finalDirection = (zDirection + rayDirection);
	finalDirection = finalDirection.normalize();

	//std::cout << finalDirection.x << ", " << finalDirection.y << ", " << finalDirection.z << std::endl;

	// Create and return the ray
	return Ray(localPosition, finalDirection);
}


void Camera::pickObject(const Vector2D& mousePos)
{
	Ray ray = screenToWorldRay(mousePos);

	for (GameObject* obj : GameObjectManager::getInstance()->getAllObjects())
	{
		Drawable* drawable = dynamic_cast<Drawable*>(obj);
		if (drawable && ray.intersects(drawable->getBoundingBox())) 
		{
			std::cout << "Selected: " << drawable->getName() << std::endl;
			break;
		}

	}
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

Matrix4x4 Camera::getProjectionMatrix()
{
	return this->projection;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Vector2D& deltaPos)
{

	if (this->mouseDown)
	{
		RECT rc = AppWindow::getInstance()->getClientWindowRect();
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		float x = localRotation.x;
		float y = localRotation.y;
		float z = localRotation.z;

		x += 0.1f * (deltaPos.y - (height / 2.0f)) * EngineTime::getDeltaTime();
		y += 0.1f * (deltaPos.x - (width / 2.0f)) * EngineTime::getDeltaTime();

		this->setRotation(x, y, z);
		this->updateViewMatrix();

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0));
	}
}

void Camera::onLeftMouseDown(const Vector2D& deltaPos)
{
	this->pickObject(deltaPos);
}

void Camera::onLeftMouseUp(const Vector2D& deltaPos)
{
}

void Camera::onRightMouseDown(const Vector2D& deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Vector2D& deltaPos)
{
	this->mouseDown = false;
}

