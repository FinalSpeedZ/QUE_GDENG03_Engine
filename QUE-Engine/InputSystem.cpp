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
    POINT current_mouse_pos = {};
    ::GetCursorPos(&current_mouse_pos);

    if (first_time)
    {
        old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
        first_time = false;
    }

    if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y)
    {
        std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

        while (it != m_set_listeners.end())
        {
            (*it)->onMouseMove(Point(current_mouse_pos.x - old_mouse_pos.x, 
									 current_mouse_pos.y - old_mouse_pos.y));

        	++it;
        }
    }
    old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

    if (::GetKeyboardState(m_keys_state))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            // Key is down
            if (m_keys_state[i] & 0x80)
            {
                std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

                while (it != m_set_listeners.end())
                {
                    if (i == VK_LBUTTON)
                    {
                        if (m_keys_state[i] != m_old_keys_state[i])
                            (*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else if (i == VK_RBUTTON)
                    {
                        if (m_keys_state[i] != m_old_keys_state[i])
                            (*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else
                        (*it)->onKeyDown(i);

                    ++it;
                }
            }

            else // Key is up
            {
                if (m_old_keys_state[i] & 0x80) // Only register the key up if it was previously down
                {
                    std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
                    while (it != m_set_listeners.end())
                    {
                        if (i == VK_LBUTTON)
                            (*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else if (i == VK_RBUTTON)
                            (*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else
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

void InputSystem::setCursorPosition(const Point& pos)
{
    ::SetCursorPos(pos.x, pos.y);
}

void InputSystem::showCursor(bool show)
{
    ::ShowCursor(show);
}

