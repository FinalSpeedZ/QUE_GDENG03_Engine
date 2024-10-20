#pragma once

#include <unordered_set>

#include "InputListener.h"
#include "Vector2D.h"

class InputSystem
{

private:
	InputSystem() {};
	~InputSystem() {};
	InputSystem(InputSystem const&) {};
	InputSystem& operator= (InputSystem const&) {};

	static InputSystem* sharedInstance;

public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

public:
	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

private:
	std::unordered_set<InputListener*> setListeners;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};

	Vector2D oldMousePos;
	bool firstTime = true;
};

