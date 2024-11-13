#pragma once
#include <vector>

#include "UIScreen.h"

class PlaceObjectScreen : public UIScreen
{
private:
	PlaceObjectScreen();
	~PlaceObjectScreen() {};

public:
	void drawUI() override;

private:
	friend class UIManager;
};

