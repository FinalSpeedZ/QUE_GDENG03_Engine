#pragma once

#include "Resource.h"
#include <d3d11.h>

class Texture : public Resource
{

public:
	Texture(const wchar_t* full_path);
	~Texture();

	ID3D11Resource* getResource();
	ID3D11ShaderResourceView* getShaderResourceView();

private:
	ID3D11Resource* texture = nullptr;
	ID3D11ShaderResourceView* shader_res_view = nullptr;

private:
	friend class DeviceContext;
};