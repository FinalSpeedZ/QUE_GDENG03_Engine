#include "Texture.h"
#include <DirectXTex.h>
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::getInstance()->getRenderSystem()->getDevice(), image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::getInstance()->getRenderSystem()->getDevice()->CreateShaderResourceView(texture, &desc,
			&shader_res_view);
	}
	else
	{
		throw std::exception("Texture not created successfully");
	}
}


Texture::~Texture()
{
	shader_res_view->Release();
	texture->Release();
}

ID3D11Resource* Texture::getResource()
{
	return texture;
}

ID3D11ShaderResourceView* Texture::getShaderResourceView()
{
	return shader_res_view;
}
