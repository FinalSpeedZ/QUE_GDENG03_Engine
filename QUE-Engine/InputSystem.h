#pragma once

#include <unordered_set>

#include "GraphicsEngine.h"

#include "Point.h"

#include "InputListener.h"

class InputSystem
{

private:
	InputSystem() {};
	~InputSystem() {};
	InputSystem(InputSystem const&) {};
	InputSystem& operator = (InputSystem const&) {};

	static InputSystem* sharedInstance;

public:
	static InputSystem* getInstance();

	static void initialize();

public:
	void update();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void clear();

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	Point old_mouse_pos;
	bool first_time = true;
};

