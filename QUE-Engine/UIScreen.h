#pragma once

#include <string>

#include "Libs/imgui/imgui.h"

class UIManager;

class UIScreen
{

protected:
	UIScreen(std::string name);
	~UIScreen() {};

public:
	virtual void drawUI() = 0;

	std::string getName();
	void setEnabled(bool enabled);

protected:
	std::string name;
	bool enabled;

protected:
	friend class UIManager;
};

