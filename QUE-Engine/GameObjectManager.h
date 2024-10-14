#pragma once

#include <memory>
#include <vector>

#include "Drawable.h"

enum class PrimitiveType
{
	// 2D Primitives
	QUAD,
	TRIANGLE,
	CIRCLE,

	// 3D Primitives
	CUBE
};

class Drawable;

class GameObjectManager
{

private:
	GameObjectManager() {};
	~GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator = (GameObjectManager const&) {};

	static GameObjectManager* sharedInstance;

public:
	static GameObjectManager* getInstance();

public:
	static void initialize();

	// Drawables
	void addPrimitives(PrimitiveType type, int count);
	void removePrimitives(PrimitiveType type, int count);

	void updateAllPrimitives(float deltaTime);
	void destroyAllPrimitives();

public:
	void rotatePrimitiveType(PrimitiveType type, float rot_x, float rot_y, float rot_z);

private:
	std::vector<std::unique_ptr<Drawable>> drawables;
};

