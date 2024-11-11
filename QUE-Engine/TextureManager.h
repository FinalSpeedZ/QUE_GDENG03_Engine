#pragma once

#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
private:
	TextureManager();
	~TextureManager() {};
	TextureManager(TextureManager const&) {};
	TextureManager& operator = (TextureManager const&) {};

	static TextureManager* sharedInstance;

public:
	static TextureManager* getInstance();

public:
	static void initialize();
	static void destroy();

	TexturePtr createTextureFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};
