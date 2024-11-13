#include "UIManager.h"

#include "GraphicsEngine.h"

#include "MenuScreen.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "InspectorScreen.h"
#include "ProfilerScreen.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer Bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->getDevice(), GraphicsEngine::getInstance()->getRenderSystem()->getContext());

	// populate UI table
	UINames uiNames;

	MenuScreen* menuScreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->uiTable[uiNames.COLOR_PICKER_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);

	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	std::cout << "[UIManager]: initialized" << std::endl;
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

void UIManager::enableUI(std::string name)
{
	this->uiTable[name]->setEnabled(true);
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		if (this->uiList[i]->enabled)
			this->uiList[i]->drawUI();
	}

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
