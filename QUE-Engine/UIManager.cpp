#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND hwnd)
{

}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::destroy()
{
	delete sharedInstance;
}
