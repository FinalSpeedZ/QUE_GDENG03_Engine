#pragma once

#include "GameObject.h"

#include "Matrix4x4.h"

class Camera : public GameObject
{

private:
	Camera();
	~Camera() {};
	Camera(Camera const&);
	Camera& operator = (Camera const&) {};

	static Camera* sharedInstance;

public:
	static Camera* getInstance();

public:
	static void initialize();

public:
	Matrix4x4 perspective();
	Matrix4x4 orthographic();

	//Vector3D getForward();
	//Vector3D getRight();

	Matrix4x4 generateWorldMatrix();

public:
	Matrix4x4 lookAt(const Vector3D& target);

	Vector3D getForward();
	void rotate(float yawDelta, float pitchDelta);

private:
	Vector3D upDirection;
	Matrix4x4 worldCam;

public:
	float forward = 0.0f;
	float rightward = 0.0f;
	float upward = 0.0f;


};

