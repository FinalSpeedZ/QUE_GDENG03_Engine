#pragma once
#include <vector>

#include "UIScreen.h"

class ProfilerScreen : public UIScreen
{
private:
	ProfilerScreen();
	~ProfilerScreen() {};

public:
	void drawUI() override;

private:
	friend class UIManager;
};

