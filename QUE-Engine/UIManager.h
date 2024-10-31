#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Window.h"
#include "UIScreen.h"

class UINames
{
public:
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const std::string PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const std::string ACTION_SCREEN = "ACTION_SCREEN";
	const std::string CONSOLE_SCREEN = "CONSOLE_SCREEN";
	const std::string MATERIAL_SCREEN = "MATERIAL_SCREEN";
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

public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1200;

private:
	std::vector<UIScreen*> UIList; // list for rendering
	std::unordered_map<std::string, UIScreen*> UITable; // access specific UI Screen (lookup table)
};

