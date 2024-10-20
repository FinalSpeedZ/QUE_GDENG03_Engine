#pragma once

#include <map>

#include "Drawable.h"

enum class PrimitiveType
{
	CAMERA,

	// 2D Primitives
	QUAD,
	TRIANGLE,
	CIRCLE,

	// 3D Primitives
	CUBE,
	PLANE,
	SPHERE
};

class GameObjectManager
{

private:
	GameObjectManager() {};
	~GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};           
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* sharedInstance;

public:
	static GameObjectManager* getInstance();

public:
	static void initialize();
	static void destroy();

public:
	void updateAll(float deltaTime);

	GameObject* findGameObjectByName(std::string name);

	void addGameObject(GameObject* gameObject);
	void createPrimitive(PrimitiveType primitive);

	void deleteGameObject(GameObject* gameObject);
	void deleteGameObjectByName(std::string name);

	std::vector<GameObject*> getAllObjects();
	std::vector<GameObject*> getObjectsByPrimitive(PrimitiveType primitive);
	GameObject* getObjectAtIndex(size_t index);
	GameObject* getLastObject();

	int activeObjects();

private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, size_t> gameObjectsIndexMap;
};

