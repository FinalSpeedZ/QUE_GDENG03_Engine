#include "MenuScreen.h"

#include <iostream>

#include "Libs/imgui/imgui.h"
#include "UIManager.h"

MenuScreen::MenuScreen()
	: UIScreen("Menu Screen")
{
	enabled = true;
}

void MenuScreen::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Profiler"))
            {
                UINames uiNames;
                UIManager::getInstance()->enableUI(uiNames.PROFILER_SCREEN);
            }

            if (ImGui::MenuItem("Color Picker"))
            {
                UINames uiNames;
                UIManager::getInstance()->enableUI(uiNames.COLOR_PICKER_SCREEN);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) 
        {
            if (ImGui::MenuItem("Credits"))
            {
                UINames uiNames;
                UIManager::getInstance()->enableUI(uiNames.CREDITS_SCREEN);
            }
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();

}
