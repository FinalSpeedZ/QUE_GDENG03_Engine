#pragma once

#include "Window.h"

#include <cstdlib> 
#include <ctime> 

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "GameObjectManager.h"

#include "InputListener.h"

#include "Vector3D.h"

#include "Vec.h"
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

	// Input
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	SwapChain* m_swap_chain;
};