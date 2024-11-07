#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "RenderSystem.h"
#include "TextureManager.h"

#include "Prerequisites.h"

class GraphicsEngine
{

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator = (GraphicsEngine const&) {};

	static GraphicsEngine* sharedInstance;

public:
	static GraphicsEngine* getInstance();

public:
	static void initialize();
	static void destroy();

	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();

private:
	RenderSystem* render_system = nullptr;
	TextureManager* texture_manager = nullptr;
};

