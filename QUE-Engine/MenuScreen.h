#pragma once
#include "UIScreen.h"

class MenuScreen : public UIScreen
{
private:
	MenuScreen();
	~MenuScreen() {};

public:
	void drawUI() override;

private:
	friend class UIManager;

};

