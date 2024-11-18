#pragma once

#include <string>
#include <vector>
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

	// 3D Primitvies Physics
	PHYSICS_CUBE,
	PHYSICS_PLANE,

	// 3D Meshes
	TEAPOT,
	BUNNY,
	ARMADILLO
};

class GameObjectManager
{

private:
	GameObjectManager();
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
	void createPrimitive(PrimitiveType primitive, std::string name = "");

	void deleteGameObject(GameObject* gameObject);
	void deleteGameObjectByName(std::string name);

	void setSelectedObject(std::string name);
	void setSelectedObject(GameObject* gameObject);
	GameObject* getSelectedObject();

	std::vector<GameObject*> getAllObjects();
	GameObject* getObjectAtIndex(size_t index);
	GameObject* getLastObject();

	int activeObjects();

private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, GameObject*> gameObjectsMap;

	GameObject* selectedObject = NULL;
};

