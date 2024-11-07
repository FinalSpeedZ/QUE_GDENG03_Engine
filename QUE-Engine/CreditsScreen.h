#pragma once
#include "UIScreen.h"

class CreditsScreen : public UIScreen
{
private:
	CreditsScreen();
	~CreditsScreen() {};

public:
	void drawUI() override;

private:
	friend class UIManager;
};

