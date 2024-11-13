#include "MenuScreen.h"

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
            if (ImGui::MenuItem("Inspector"))
            {
                UINames uiNames;
                UIManager::getInstance()->enableUI(uiNames.INSPECTOR_SCREEN);
            }

            if (ImGui::MenuItem("Hierarchy"))
            {
                UINames uiNames;
                UIManager::getInstance()->enableUI(uiNames.HIERARCHY_SCREEN);
            }

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
