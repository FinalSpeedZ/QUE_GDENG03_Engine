#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }

	try
	{
		mesh_manager = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not created successfully"); }


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(mesh_layout_byte_code, shader_byte_code, size_shader);
	mesh_layout_size = size_shader;
	render_system->releaseCompiledShader();

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

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = mesh_layout_byte_code;
	*size = mesh_layout_size;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return render_system;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return mesh_manager;
}

