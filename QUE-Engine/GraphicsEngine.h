#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

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

	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	MeshManager* getMeshManager();
	RenderSystem* getRenderSystem();

private:
	MeshManager* mesh_manager = nullptr;
	RenderSystem* render_system = nullptr;

	unsigned char mesh_layout_byte_code[1024];
	size_t mesh_layout_size = 0;
};

