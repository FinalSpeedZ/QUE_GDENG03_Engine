#pragma once

#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
protected:
	ResourceManager() {};
	virtual ~ResourceManager() {};

private:
	ResourceManager(ResourceManager const&) {};            
	ResourceManager& operator=(ResourceManager const&) {};

public:
	ResourcePtr createResourceFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;

private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;

};
