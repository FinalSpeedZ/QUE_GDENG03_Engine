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

	std::memset(sharedInstance->m_keys_state, 0, sizeof(sharedInstance->m_keys_state));
	std::memset(sharedInstance->m_old_keys_state, 0, sizeof(sharedInstance->m_old_keys_state));
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
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = setListeners.begin();

				while (it != setListeners.end())
				{
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
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
