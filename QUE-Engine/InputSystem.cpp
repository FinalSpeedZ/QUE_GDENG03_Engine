#include "InputSystem.h"

#include "AppWindow.h"

InputSystem* InputSystem::sharedInstance = NULL;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();

	std::memset(sharedInstance->keysState, 0, sizeof(sharedInstance->keysState));
	std::memset(sharedInstance->oldKeysState, 0, sizeof(sharedInstance->oldKeysState));
}

void InputSystem::destroy()
{
	if (sharedInstance != NULL) 
	{
		delete sharedInstance;
	}
}

void InputSystem::update()
{
	POINT currMousePos = {};
	::GetCursorPos(&currMousePos);

	if (firstTime)
	{
		oldMousePos = Vector2D(currMousePos.x, currMousePos.y);
		firstTime = false;
	}

	if (currMousePos.x != oldMousePos.x || currMousePos.y != oldMousePos.y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::unordered_set<InputListener*>::iterator it = setListeners.begin();

		while (it != setListeners.end())
		{
			(*it)->onMouseMove(Vector2D(currMousePos.x, currMousePos.y));
			++it;
		}
	}
	oldMousePos = Vector2D(currMousePos.x, currMousePos.y);


	if (::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = setListeners.begin();

				while (it != setListeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onLeftMouseDown(Vector2D(currMousePos.x, currMousePos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onRightMouseDown(Vector2D(currMousePos.x, currMousePos.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			else // KEY IS UP
			{
				if (keysState[i] != oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Vector2D(currMousePos.x, currMousePos.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Vector2D(currMousePos.x, currMousePos.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}

			}
		}
		// store current keys state to old keys state buffer
		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	setListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	setListeners.erase(listener);
}

void InputSystem::setCursorPosition(const Vector2D& pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}
