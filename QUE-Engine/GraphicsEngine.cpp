#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("Graphics Engine not created successfully"); }
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::sharedInstance = nullptr;
	delete m_render_system;
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
	return m_render_system;
}
