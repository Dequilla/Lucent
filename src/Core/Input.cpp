#include "Input.h"

void ce::core::Input::checkInput(const SDL_Event& e)
{
	// KEYBOARD EVENTS
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
		for (auto &ptr : m_boundKeys)
		{
			// If keyDown keyPressed = true
			bool keyPressed = (e.type == SDL_KEYDOWN) ? true : false;

			// If the current key is equal to the bound key
			if (e.key.keysym.sym == ptr)
			{
				// Call callback function
				m_cbKeyboardEvent.at(ptr)(keyPressed);
			}
		
		}
	}
	// AXIS EVENTS
	else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL)
	{
		for (auto &ptr : m_boundAxis)
		{
			switch (ptr)
			{
			case M_MOTION_X:
				m_cbAxisEvent.at(ptr)((float)e.motion.x);
				break;
			case M_MOTION_Y:
				m_cbAxisEvent.at(ptr)((float)e.motion.y);
				break;
			case M_MOTION_XREL:
				m_cbAxisEvent.at(ptr)((float)e.motion.xrel);
				break;
			case M_MOTION_YREL:
				m_cbAxisEvent.at(ptr)((float)e.motion.yrel);
				break;
			case M_WHEEL_X:
				m_cbAxisEvent.at(ptr)((float)e.wheel.x);
				break;
			case M_WHEEL_Y:
				m_cbAxisEvent.at(ptr)((float)e.wheel.y);
				break;
			}
		}
	}
}