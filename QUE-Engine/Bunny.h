#pragma once
#include "Drawable.h"

class Bunny : public Drawable
{

public:
	Bunny(std::string name = "Bunny");
	~Bunny() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

private:
	void updateConstantBuffer(float deltaTime) override;
	void projectionViewMatrix() override;
};

