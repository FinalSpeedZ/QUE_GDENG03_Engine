#include "GameObjectManager.h"

#include <iostream>
#include <ostream>

#include "Drawable.h"
#include "Circle.h"
#include "Cube.h"
#include "Quad.h"
#include "Triangle.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{

    sharedInstance = new GameObjectManager();
}

void GameObjectManager::addPrimitives(PrimitiveType type, int count)
{
    for (int i = 0; i < count; ++i) {
        switch (type) {
        case PrimitiveType::CUBE:
            drawables.push_back(std::make_unique<Cube>("Cube " + std::to_string(drawables.size() + 1)));
            drawables.back()->onCreate();
            break;

        case PrimitiveType::QUAD:
            drawables.push_back(std::make_unique<Quad>("Triangle " + std::to_string(drawables.size() + 1)));
            drawables.back()->onCreate();
        	break;

        case PrimitiveType::TRIANGLE:
            drawables.push_back(std::make_unique<Triangle>("Triangle " + std::to_string(drawables.size() + 1)));
            drawables.back()->onCreate();
        	break;

        case PrimitiveType::CIRCLE:
            drawables.push_back(std::make_unique<Circle>("Circle " + std::to_string(drawables.size() + 1)));
            drawables.back()->onCreate();
        	break;

        default:
            break;
        }
    }

    std::cout << "Count of Drawables: " << drawables.size() << std::endl;
}

void GameObjectManager::removePrimitives(PrimitiveType type, int count)
{
	std::string typeName;
	switch (type)
	{
		case PrimitiveType::CUBE: typeName = "Cube"; break;
		case PrimitiveType::QUAD: typeName = "Quad"; break;
		case PrimitiveType::TRIANGLE: typeName = "Triangle"; break;
		case PrimitiveType::CIRCLE: typeName = "Circle"; break;
		default: return; 
	}

	for (auto it = drawables.rbegin(); it != drawables.rend() && count > 0;)
	{
	    if ((*it)->getName().find(typeName) != std::string::npos)
	    {
	        it = std::vector<std::unique_ptr<GameObject>>::reverse_iterator(drawables.erase(std::next(it).base()));
	    }
	    else
	    {
	        ++it; 
	    }
	}
}

void GameObjectManager::updateAllPrimitives(float deltaTime)
{
    for (auto& drawable : drawables) {
        drawable->onUpdate(deltaTime);
    }
}

void GameObjectManager::destroyAllPrimitives()
{
    for (auto& drawable : drawables) {
        drawable->onDestroy();
    }
    drawables.clear();
}


