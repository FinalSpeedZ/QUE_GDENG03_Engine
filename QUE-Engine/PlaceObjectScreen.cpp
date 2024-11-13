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

    if (ImGui::Button("Cube"))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
    }
    if (ImGui::Button("Plane"))
    {
        GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);
    }

	ImGui::End();

}
