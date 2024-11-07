#include "CreditsScreen.h"

#include <iostream>

#include "imgui.h"

CreditsScreen::CreditsScreen()
    : UIScreen("Credits Screen")
{
    enabled = false;
}

void CreditsScreen::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiCond_Always);

	ImGui::Begin("Credits", nullptr);

	ImGui::PushTextWrapPos(ImGui::GetWindowSize().x - 20);
	ImGui::TextColored(ImVec4(0.75f, 0.043f, 0.031f, 1), "QUEngine Scene Editor V0.01");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "Developer: Zachary Gadjiel Breinard Que");
	ImGui::TextColored(ImVec4(1, 1, 1, 1), "This is the first version of my scene editor for GDENG03 Class. \nRecent changes: Added UI Credits\n\n\n");
	ImGui::PopTextWrapPos();

	float buttonWidth = 100.0f;
	float availableWidth = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX((availableWidth - buttonWidth) * 0.5f); 

	if (ImGui::Button("Close", ImVec2(buttonWidth, 0)))
	{
		enabled = false;

	}

	ImGui::End();

}
