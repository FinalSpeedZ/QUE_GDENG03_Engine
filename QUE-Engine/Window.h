#pragma once
#include <iostream>
#include <Windows.h>

#include "EngineTime.h"

class Window
{

public:
	Window() {};
	~Window() {};

	// initialize the window
	bool init();
	bool broadcast();
	// release the window
	bool release();
	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	// EVENTS
	virtual void onCreate() {};
	virtual void onUpdate() {};
	virtual void onDestroy();

	virtual void onFocus() {};
	virtual void onKillFocus() {};

protected:
	HWND m_hwnd;
	bool m_is_run;
};

