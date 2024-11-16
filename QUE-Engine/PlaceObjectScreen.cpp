#include "PlaceObjectScreen.h"

#include "GameObjectManager.h"
#include "UIManager.h"

PlaceObjectScreen::PlaceObjectScreen()
	: UIScreen("Place Object Screen")
{
}

void PlaceObjectScreen::drawUI()
{
	ImGui::Begin("Place Objects", &enabled);

    ImGui::Text("3D Primitives");
    ImGui::Separator();  

    float windowWidth = ImGui::GetWindowSize().x;

    float buttonWidth = windowWidth - 15;
    float buttonHeight = 20;

    if (ImGui::Button("Physics Cube", ImVec2(buttonWidth, buttonHeight)))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
    }

    if (ImGui::Button("Physics Cube x20", ImVec2(buttonWidth, buttonHeight)))
    {
        for (int i = 0; i < 20; i++)
        {
            GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
        }
    }

    if (ImGui::Button("Plane", ImVec2(buttonWidth, buttonHeight)))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);
    }

    ImGui::NewLine();

    ImGui::Text("3D Meshes");
    ImGui::Separator();

    if (ImGui::Button("Teapot", ImVec2(buttonWidth, buttonHeight)))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::TEAPOT);
    }
    if (ImGui::Button("Bunny", ImVec2(buttonWidth, buttonHeight)))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::BUNNY);
    }
    if (ImGui::Button("Armadillo", ImVec2(buttonWidth, buttonHeight)))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::ARMADILLO);
    }

	ImGui::End();

}
