#include "GameObjectManager.h"

#include "Armadillo.h"
#include "Bunny.h"
#include "Camera.h"
#include "GameObject.h"
#include "Drawable.h"
#include "Triangle.h"
#include "Quad.h"
#include "Circle.h"
#include "Cube.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "Plane.h"
#include "Teapot.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
	std::cout << "[GameObjectManager]: initialized" << std::endl;
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	sharedInstance->gameObjects.clear();
	sharedInstance->gameObjectsMap.clear();

	delete sharedInstance;
}

void GameObjectManager::updateAll(float deltaTime)
{
	for (const auto& object : gameObjects) 
	{
		if (object->isActive()) 
		{
			object->onUpdate(deltaTime);
		}
	}
}

GameObject* GameObjectManager::findGameObjectByName(std::string name)
{
	auto it = this->gameObjectsMap.find(name);

	if (it != this->gameObjectsMap.end())
	{
		return it->second; 
	}
	else
	{
		return nullptr; 
	}
}

void GameObjectManager::addGameObject(GameObject* gameObject)
{
	std::string baseName = gameObject->getName();
	std::string name = baseName;
	int count = 1;

	while (gameObjectsMap.find(name) != gameObjectsMap.end())
	{
		name = baseName + " (" + std::to_string(count) + ")";
		count++;
	}

	gameObject->setName(name);
	gameObjectsMap[name] = gameObject;
	gameObjects.push_back(gameObject);
}

void GameObjectManager::createPrimitive(PrimitiveType primitive, std::string name)
{

	if (primitive == PrimitiveType::CAMERA)
	{
		Camera* camera;
		if (name.empty())
			camera = new Camera();
		else
			camera = new Camera(name);

		addGameObject(camera);
	}

	else if (primitive == PrimitiveType::QUAD)
	{
		Quad* quad;
		if (name.empty())
			quad = new Quad();
		else
			quad = new Quad(name);

		addGameObject(quad);
	}

	else if (primitive == PrimitiveType::TRIANGLE)
	{
		Triangle* triangle;
		if (name.empty())
			triangle = new Triangle();
		else 
			triangle = new Triangle(name);

		addGameObject(triangle);
	}

	else if (primitive == PrimitiveType::CIRCLE)
	{
		Circle* circle;
		if (name.empty())
			circle = new Circle();
		else
			circle = new Circle(name);

		addGameObject(circle);
	}

	else if (primitive == PrimitiveType::CUBE)
	{
		Cube* cube;
		if (name.empty())
			cube = new Cube();
		else
			cube = new Cube(name);

		addGameObject(cube);
	}

	else if (primitive == PrimitiveType::PLANE)
	{
		Plane* plane;
		if (name.empty())
			plane = new Plane();
		else
			plane = new Plane(name);

		addGameObject(plane);
	}

	else if (primitive == PrimitiveType::PHYSICS_CUBE)
	{
		PhysicsCube* cube;
		if (name.empty())
			cube = new PhysicsCube();
		else
			cube = new PhysicsCube(name);

		addGameObject(cube);
	}

	else if (primitive == PrimitiveType::PHYSICS_PLANE)
	{
		PhysicsPlane* plane;
		if (name.empty())
			plane = new PhysicsPlane();
		else
			plane = new PhysicsPlane(name);

		addGameObject(plane);
	}

	else if (primitive == PrimitiveType::TEAPOT)
	{
		Teapot* teapot;
		if (name.empty())
			teapot = new Teapot();
		else
			teapot = new Teapot(name);

		addGameObject(teapot);
	}

	else if (primitive == PrimitiveType::BUNNY)
	{
		Bunny* bunny;
		if (name.empty())
			bunny = new Bunny();
		else
			bunny = new Bunny(name);

		addGameObject(bunny);
	}

	else if (primitive == PrimitiveType::ARMADILLO)
	{
		Armadillo* armadillo;
		if (name.empty())
			armadillo = new Armadillo();
		else
			armadillo = new Armadillo(name);

		addGameObject(armadillo);
	}
}

void GameObjectManager::deleteGameObject(GameObject* gameObject)
{
	if (gameObject)
	{
		auto it = gameObjectsMap.find(gameObject->getName());
		if (it != gameObjectsMap.end())
		{
			gameObjectsMap.erase(it);
		}

		auto vecIt = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
		if (vecIt != gameObjects.end())
		{
			gameObjects.erase(vecIt);
		}

		delete gameObject;
	}
}

void GameObjectManager::deleteGameObjectByName(std::string name)
{
	GameObject* obj = findGameObjectByName(name);
	if (obj) 
	{
		deleteGameObject(obj);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	auto it = this->gameObjectsMap.find(name);
	if (it != this->gameObjectsMap.end())
	{
		this->setSelectedObject(it->second);
	}
}

void GameObjectManager::setSelectedObject(GameObject* gameObject)
{
	this->selectedObject = gameObject;
}

GameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}


std::vector<GameObject*> GameObjectManager::getAllObjects()
{
	std::vector<GameObject*> objects;

	for (const auto& object : gameObjects) 
	{
		objects.push_back(object);
	}

	return objects;
}

GameObject* GameObjectManager::getObjectAtIndex(size_t index)
{
	if (index < gameObjects.size()) 
	{
		return gameObjects[index];
	}
	else 
	{
		return nullptr;
	}
}

GameObject* GameObjectManager::getLastObject()
{
	if (!gameObjects.empty())
	{
		return gameObjects.back();
	}
	else 
	{
		return nullptr;
	}
}

int GameObjectManager::activeObjects()
{
	return static_cast<int>(gameObjects.size());
}

