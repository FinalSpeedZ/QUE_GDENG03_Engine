#include "InputSystem.h"

#include <iostream>

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

void InputSystem::update()
{
    if (::GetKeyboardState(m_keys_state))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            // Key is down
            if (m_keys_state[i] & 0x80)
            {
                if (!(m_old_keys_state[i] & 0x80)) // Only register the key down if it was previously up
                {
                    std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
                    while (it != m_set_listeners.end())
                    {
                        (*it)->onKeyDown(i);
                        ++it;
                    }
                }
            }
            else // Key is up
            {
                if (m_old_keys_state[i] & 0x80) // Only register the key up if it was previously down
                {
                    std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
                    while (it != m_set_listeners.end())
                    {
                        (*it)->onKeyUp(i);
                        ++it;
                    }
                }
            }
        }
        // Store current key state to old key state
        ::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
    }
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::clear()
{
	std::memset(sharedInstance->m_keys_state, 0, sizeof(sharedInstance->m_keys_state));
	std::memset(sharedInstance->m_old_keys_state, 0, sizeof(sharedInstance->m_old_keys_state));
}
