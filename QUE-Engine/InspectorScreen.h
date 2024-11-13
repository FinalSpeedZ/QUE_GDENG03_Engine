#pragma once
#include <vector>

#include "GameObject.h"
#include "UIScreen.h"

class InspectorScreen : public UIScreen
{
private:
	InspectorScreen();
	~InspectorScreen() {};

public:
	void drawUI() override;

private:
	void drawTransform();

private:
	friend class UIManager;

	GameObject* gameObject = NULL;
};

