#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"

enum class PrimitiveType
{
	// 2D Primitives
	QUAD,
	TRIANGLE,
	CIRCLE,

	// 3D Primitives
	CUBE
};

class GameObject;

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

private:
	std::vector<std::unique_ptr<GameObject>> drawables;
};

