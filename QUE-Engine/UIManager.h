#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "Libs/imgui/imgui.h"
#include "Libs/imgui/imgui_impl_dx11.h"
#include "Libs/imgui/imgui_impl_win32.h"
#include "Window.h"
#include "UIScreen.h"

class UINames
{

public:
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string CREDITS_SCREEN = "CREDITS_SCREEN";
	const std::string COLOR_PICKER_SCREEN = "COLOR_PICKER_SCREEN";
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const std::string PLACE_OBJECT_SCREEN = "HIERARCHY_SCREEN";
};

class UIManager
{
private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator = (UIManager const&) {};

	static UIManager* sharedInstance;

public:
	static UIManager* getInstance();

public:
	static void initialize(HWND hwnd);
	static void destroy();

	void enableUI(std::string name);

	void drawAllUI();

public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

private:
	std::vector<UIScreen*> uiList; // list for rendering
	std::unordered_map<std::string, UIScreen*> uiTable; // access specific UI Screen (lookup table)
};
