#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"

Camera* Camera::sharedInstance = NULL;

Camera::Camera()
	: GameObject("World Camera")
{
	localPosition.z = -1;
	upDirection = { 0.0f, 1.0f, 0.0f };

	worldCam.setTranslation(Vector3D(0, 0, -2));
}

Camera::Camera(Camera const&)
	: GameObject("World Camera")
{
}

Camera* Camera::getInstance()
{
	return sharedInstance;
}

void Camera::initialize()
{
	sharedInstance = new Camera();
}

Matrix4x4 Camera::perspective()
{

	float width = AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left;
	float height = AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top;

	Matrix4x4 perspective;

	float fov = 60.0f * M_PI / 180;
	float znear = 0.1f;
	float zfar = 100.0f;

	perspective.setPerspectiveFovLH(fov, width/height, znear, zfar);

	return perspective;

}

Matrix4x4 Camera::orthographic()
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();

	Matrix4x4 ortho;

	float scalingFactor = 300.0f;

	float near_plane = -4.0f;
	float far_plane = 4.0f;

	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	ortho.setOrthoLH
	(
		width / scalingFactor,
		height / scalingFactor,
		near_plane,
		far_plane
	);

	return ortho;
}

Matrix4x4 Camera::generateWorldMatrix()
{
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	// Calculate the forward and right directions based on the camera's orientation
	Vector3D forwardDirection = getForward(); // Camera's forward vector
	Vector3D rightDirection = upDirection.cross(forwardDirection).normalize(); // Right vector, perpendicular to forward and up

	// Update the camera's position based on inputs
	localPosition += forwardDirection * forward * 0.1f; // Forward/backward movement
	localPosition += rightDirection * rightward * 0.1f; // Left/right movement
	localPosition.y += upward * 0.1f; // Up/down movement

	// Set the translation in the world matrix
	world_cam.setTranslation(localPosition);

	// Apply the rotations to the camera
	world_cam.setRotationX(localRotation.x);
	world_cam.setRotationY(localRotation.y);
	world_cam.setRotationZ(localRotation.z);

	// Invert the matrix to get the view transformation
	world_cam.inverse();

	return world_cam;

	return world_cam;
}

Vector3D Camera::getForward()
{
	Vector3D forward;
	float yawRadians = localRotation.y * (M_PI / 180.0f);
	float pitchRadians = localRotation.x * (M_PI / 180.0f);

	forward.x = cos(pitchRadians) * sin(yawRadians);
	forward.y = sin(pitchRadians);
	forward.z = cos(pitchRadians) * cos(yawRadians);
	forward.normalize();

	return forward;
}

void Camera::rotate(float yawDelta, float pitchDelta)
{
	localRotation.y += yawDelta; // Yaw
	localRotation.x += pitchDelta; // Pitch

	// Clamp pitch to avoid gimbal lock
	if (localRotation.x > 89.0f) localRotation.x = 89.0f;
	if (localRotation.x < -89.0f) localRotation.x = -89.0f;

	// Normalize yaw
	if (localRotation.y < 0.0f) localRotation.y += 360.0f;
	if (localRotation.y >= 360.0f) localRotation.y -= 360.0f;
}


