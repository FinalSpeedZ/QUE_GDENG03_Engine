#pragma once

#include "Window.h"

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "Vector3D.h"

#include "Vec.h"
#include "Colors.h"
#include "Vertex.h"

class AppWindow : public Window
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

private:
	SwapChain* m_swap_chain;
};