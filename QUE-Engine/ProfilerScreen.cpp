#include "ProfilerScreen.h"

#include "UIManager.h"

ProfilerScreen::ProfilerScreen()
	: UIScreen("Profiler Screen")
{
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Profiler", &enabled);

	ImGui::Text("Average Frame Time: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();

}
