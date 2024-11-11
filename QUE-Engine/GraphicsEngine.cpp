#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }

	std::cout << "[GraphicsEngine]: initialized" << std::endl;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::sharedInstance = nullptr;
	delete render_system;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	if (GraphicsEngine::sharedInstance)
		throw std::exception("Graphics Engine already created");

	sharedInstance = new GraphicsEngine();
}

void GraphicsEngine::destroy()
{
	if (!GraphicsEngine::sharedInstance)
		return;
	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return render_system;
}


