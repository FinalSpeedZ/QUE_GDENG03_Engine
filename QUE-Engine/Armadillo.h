#pragma once
#include "Drawable.h"

class Armadillo : public Drawable
{

public:
	Armadillo(std::string name = "Armadillo");
	~Armadillo() {};

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

