#pragma once
#include "UIScreen.h"

class ColorPickerScreen : public UIScreen
{
private:
	ColorPickerScreen();
	~ColorPickerScreen() {};

public:
	void drawUI() override;

private:
	float color[4] = { 0,0,0,0 };

	friend class UIManager;
};



