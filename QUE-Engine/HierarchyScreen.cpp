#include "HierarchyScreen.h"

#include "GameObjectManager.h"
#include "UIManager.h"

HierarchyScreen::HierarchyScreen()
	: UIScreen("Hierarchy Screen")
{
}

void HierarchyScreen::drawUI()
{
    ImGui::Begin("Hierarchy", &enabled);

    std::vector<GameObject*> objectList = GameObjectManager::getInstance()->getAllObjects();

    for (int i = 0; i < objectList.size(); i++)
    {
        std::string name = objectList[i]->getName();

        float windowWidth = ImGui::GetWindowSize().x;

        float buttonWidth = windowWidth - 15;  
        float buttonHeight = 20;

        if (ImGui::Button(name.c_str(), ImVec2(buttonWidth, buttonHeight)))
        {
            GameObjectManager::getInstance()->setSelectedObject(name);
        }
    }

    ImGui::End();
}
