#pragma once
#include "GameObject.h"

class Camera : public GameObject
{

public:
	Camera();
	Camera(std::string name);
	~Camera() {};

public:
	virtual void onCreate() override;
	virtual void onUpdate(float deltatime) override;
	virtual void onDestroy() override;

private:
	void updateMatrix();
	Matrix4x4 getOrthoMatrix();
	Matrix4x4 getPersMatrix();

public:
	constant getUpdatedConstantData();

private:
	constant worldViewProj;
	Matrix4x4 worldCam;

public:
	float forward = 0.0f;
	float rightward = 0.0f;
	float upward = 0.0f;

};

