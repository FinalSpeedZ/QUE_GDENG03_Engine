#pragma once

#include "Window.h"

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "InputListener.h"

#include "GameObjectManager.h"

#include "Colors.h"
#include "Vertex.h"

class AppWindow : public Window, public InputListener
{

private:
	AppWindow() {};
	~AppWindow() {};
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};

	static AppWindow* sharedInstance;

public:
	static AppWindow* getInstance();

public:
	static void initialize();

public:
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// KEYBOARD
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	// MOUSE
	virtual void onMouseMove(const Vector2D& deltaMousePos) override;
	virtual void onLeftMouseDown(const Vector2D& mousePos) override;
	virtual void onLeftMouseUp(const Vector2D& mousePos) override;
	virtual void onRightMouseDown(const Vector2D& mousePos) override;
	virtual void onRightMouseUp(const Vector2D& mousePos) override;

private:
	SwapChain* m_swap_chain;

};