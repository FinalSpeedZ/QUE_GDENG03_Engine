#include "ShaderLibrary.h"

#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary::ShaderLibrary()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = graphicsEngine->getRenderSystem();

	ShaderNames shaderNames;
	ShaderData shaderData;
	renderSystem->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	std::cout << "[ShaderLibrary]: initialized" << std::endl;
}

ShaderLibrary::~ShaderLibrary()
{
	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

void ShaderLibrary::requestPixelShaderData(std::wstring pixelShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->getRenderSystem()->compilePixelShader(pixelShaderName.c_str(), "psmain", shaderByteCode, sizeShader);
}

VertexShaderPtr ShaderLibrary::getVertexShader(std::wstring vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
		std::cout << "Vertex Shader " << vertexShaderName.c_str() << " not found" << std::endl;
	return this->activeVertexShaders[vertexShaderName];
}

PixelShaderPtr ShaderLibrary::getPixelShader(std::wstring pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL)
		std::cout << "Pixel Shader " << pixelShaderName.c_str() << " not found" << std::endl;
	return this->activePixelShaders[pixelShaderName];
}
