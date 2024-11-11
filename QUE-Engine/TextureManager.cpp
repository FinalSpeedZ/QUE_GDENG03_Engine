#include "TextureManager.h"

#include <iostream>

#include "Texture.h"

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager::TextureManager() : ResourceManager()
{
	std::cout << "[TextureManager]: initialized" << std::endl;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

void TextureManager::initialize()
{
	if (TextureManager::sharedInstance)
		throw std::exception("TextureManager already created");

	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	if (!TextureManager::sharedInstance)
		return;
	delete sharedInstance;
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}