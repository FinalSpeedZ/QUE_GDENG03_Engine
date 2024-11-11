#include "CreditsScreen.h"

#include <iostream>

#include "GraphicsEngine.h"
#include "Libs/imgui/imgui.h"
#include "Texture.h"

CreditsScreen::CreditsScreen()
    : UIScreen("Credits Screen")
{
    enabled = false;
}

void CreditsScreen::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(350, 0), ImGuiCond_Always);

	ImGui::Begin("Credits", nullptr);

	TexturePtr tex = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/Logo.jpg");

	float imageWidth = 290.0f;
	float availableWidth = ImGui::GetContentRegionAvail().x;
	float centerX = (availableWidth - imageWidth) * 0.5f;

	ImGui::SetCursorPosX(centerX);
	ImGui::Image((ImTextureID)tex->getShaderResourceView(), ImVec2(290, 290));

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::PushTextWrapPos(ImGui::GetWindowSize().x - 20);
	ImGui::TextColored(ImVec4(0.75f, 0.043f, 0.031f, 1), "QUEngine Scene Editor V0.01");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "Developer: Zachary Gadjiel Breinard Que");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "This is the first version of my scene editor for GDENG03 Class.");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "Acknowledgements: \nDoc Neil Gallego as our teacher for GDENG03 Class\nPardCode for creating wonderful Youtube Tutorials");
	ImGui::PopTextWrapPos();

	float buttonWidth = 100.0f;
	availableWidth = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX((availableWidth - buttonWidth) * 0.5f); 

	if (ImGui::Button("Close", ImVec2(buttonWidth, 0)))
	{
		enabled = false;

	}

	ImGui::End();

}
