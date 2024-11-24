#pragma once

#include <unordered_map>
#include <string>

#include "Prerequisites.h"

class VertexShader;
class PixelShader;

class ShaderNames
{
public:
	// Vertex Shader
	const std::wstring BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const std::wstring TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";

	// Pixel Shader
	const std::wstring BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const std::wstring TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData
	{
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	ShaderLibrary& operator = (ShaderLibrary const&) {};

	static ShaderLibrary* sharedInstance;

public:
	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	void requestPixelShaderData(std::wstring pixelShaderName, void** shaderByteCode, size_t* sizeShader);
	VertexShaderPtr getVertexShader(std::wstring vertexShaderName);
	PixelShaderPtr getPixelShader(std::wstring pixelShaderName);

private:
	std::unordered_map<std::wstring, VertexShaderPtr> activeVertexShaders;
	std::unordered_map<std::wstring, PixelShaderPtr> activePixelShaders;

};
