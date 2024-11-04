#include "AppWindow.h"

#include <corecrt_math_defines.h>

#include "Camera.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::initialize();

	InputSystem::initialize();

	GameObjectManager::initialize();

	SceneCameraHandler::initialize();

	ImGui::CreateContext();
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->getDevice(), GraphicsEngine::getInstance()->getRenderSystem()->getContext());
	ImGui_ImplWin32_Init(this->m_hwnd);


	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < 10; i++)
	{
		GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
	}

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	if (isRunning())
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.5f, 0.5f, 0.8f, 1);

		RECT rc = this->getClientWindowRect();
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		GameObjectManager::getInstance()->updateAll(EngineTime::getDeltaTime());

		SceneCameraHandler::getInstance()->update();


		if (ui_running)
		{
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::StyleColorsDark();

			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.4f, 0.0f, 0.0f, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.4f, 0.0f, 0.0f, 0.5f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.0f, 0.0f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5f, 0.0f, 0.0f, 1.00f);

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiCond_Always);

			ImGui::Begin("About", nullptr);

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
				ui_running = false;
			}

			ImGui::End();

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}

		m_swap_chain->present(true);
	}
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::onFocus()
{
	Window::onFocus();

	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();

	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	int Esc = 27;


	if (key == Esc)
	{
		onDestroy();
	}
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Vector2D& mousePos)
{

}

void AppWindow::onLeftMouseDown(const Vector2D& mousePos)
{

}

void AppWindow::onLeftMouseUp(const Vector2D& mousePos)
{

}

void AppWindow::onRightMouseDown(const Vector2D& mousePos)
{

}

void AppWindow::onRightMouseUp(const Vector2D& mousePos)
{

}


