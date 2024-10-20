#include "GameObjectManager.h"

#include "GameObject.h"
#include "Drawable.h"
#include "Triangle.h"
#include "Quad.h"
#include "Circle.h"
#include "Cube.h"
#include "Plane.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

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
	sharedInstance->gameObjectsIndexMap.clear();

	delete sharedInstance;
}

void GameObjectManager::updateAll(float deltaTime)
{
	for (const auto& object : gameObjects) 
	{
		if (object) 
		{
			object->onUpdate(deltaTime);
		}
	}
}

GameObject* GameObjectManager::findGameObjectByName(std::string name)
{
	auto it = gameObjectsIndexMap.find(name);

	if (it != gameObjectsIndexMap.end()) 
	{
		return gameObjects[it->second];
	}

	else 
	{
		return nullptr;
	}
}

void GameObjectManager::addGameObject(GameObject* gameObject)
{
	if (gameObjectsIndexMap.find(gameObject->getName()) != gameObjectsIndexMap.end())
	{
		int count = 1;
		std::string name = gameObject->getName() + " (" + std::to_string(count) + ")";

		while (gameObjectsIndexMap.find(name) != gameObjectsIndexMap.end()) 
		{
			count++;
			name = gameObject->getName() + " (" + std::to_string(count) + ")";
		}

		gameObject->setName(name);
	}

	gameObjectsIndexMap[gameObject->getName()] = gameObjects.size();
	gameObjects.push_back(gameObject);
	gameObject->onCreate();
}

void GameObjectManager::createPrimitive(PrimitiveType primitive)
{
	if (primitive == PrimitiveType::CUBE)
	{
		Cube* cube = new Cube();
		addGameObject(cube);
	}
}

void GameObjectManager::deleteGameObject(GameObject* gameObject)
{
	if (gameObject) 
	{
		auto it = gameObjectsIndexMap.find(gameObject->getName());

		if (it != gameObjectsIndexMap.end()) 
		{
			size_t index = it->second;

			gameObjects.erase(gameObjects.begin() + index);
			gameObjectsIndexMap.erase(it);

			for (size_t i = index; i < gameObjects.size(); ++i) 
			{
				gameObjectsIndexMap[gameObjects[i]->getName()] = i; 
			}
		}
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

