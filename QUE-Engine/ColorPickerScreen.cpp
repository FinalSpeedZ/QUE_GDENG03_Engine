#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen()
	: UIScreen("Color Picker Screen")
{
	enabled = false;
}

void ColorPickerScreen::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(300, 0), ImGuiCond_Always);

	ImGui::Begin("Color Picker", &enabled);

	if (ImGui::ColorPicker4("Color", color, ImGuiColorEditFlags_PickerHueWheel))
	{
	};

	ImGui::End();

}
