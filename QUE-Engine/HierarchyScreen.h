#pragma once
#include <vector>

#include "UIScreen.h"

class HierarchyScreen : public UIScreen
{
private:
	HierarchyScreen();
	~HierarchyScreen() {};

public:
	void drawUI() override;

private:
	friend class UIManager;
};

