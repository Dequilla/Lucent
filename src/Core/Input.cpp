#include "Input.h"

void ce::core::Input::unbindActual()
{
	// Unbinds if it was requested

	if (m_bUnbindButtons)
	{
		if (!m_cbButtonEvent.empty())
			m_cbButtonEvent.clear();
		if (!m_boundKeys.empty())
			m_boundKeys.clear();

		m_bUnbindButtons = false;
	}
	
	if (m_bUnbindAxis)
	{
		if (!m_cbAxisEvent.empty())
			m_cbAxisEvent.clear();
		if (!m_boundAxis.empty())
			m_boundAxis.clear();

		m_bUnbindAxis = false;
	}
}

void ce::core::Input::checkInput(const SDL_Event& e)
{
	// Checks if a unbind has been requested
	unbindActual();

	// KEYBOARD/BUTTON EVENTS
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		try
		{
			for (auto &ptr : m_boundKeys)
			{
				// If key/button is pressed keyPressed = true
				bool keyPressed = (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) ? true : false;

				// Check if it equals a key
				if (e.key.keysym.sym == ptr)
				{
					// Call callback function
					m_cbButtonEvent.at(ptr)(keyPressed);
				}
			
				// Check if it is a mouse button
				if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
				{
					// If current bind we are checking equals any of the mouse buttons
					switch (ptr)
					{
					case M_BUTTON_LEFT:
						if (e.button.button == SDL_BUTTON_LEFT)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case M_BUTTON_RIGHT:
						if (e.button.button == SDL_BUTTON_RIGHT)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case M_BUTTON_MIDDLE:
						if (e.button.button == SDL_BUTTON_MIDDLE)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case M_BUTTON_X1:
						if (e.button.button == SDL_BUTTON_X1)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case M_BUTTON_X2:
						if (e.button.button == SDL_BUTTON_X2)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					}
				}
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Exception in - CheckInput: " << e.what() << std::endl;
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
				if(e.type == SDL_MOUSEMOTION && e.motion.xrel != 0)
					m_cbAxisEvent.at(ptr)((float)e.motion.x);
				break;
			case M_MOTION_Y:
				if(e.type == SDL_MOUSEMOTION && e.motion.yrel != 0)
					m_cbAxisEvent.at(ptr)((float)e.motion.y);
				break;
			case M_MOTION_XREL:
				if (e.type == SDL_MOUSEMOTION && e.motion.xrel != 0)
					m_cbAxisEvent.at(ptr)((float)e.motion.xrel);
				break;
			case M_MOTION_YREL:
				if (e.type == SDL_MOUSEMOTION && e.motion.yrel != 0)
					m_cbAxisEvent.at(ptr)((float)e.motion.yrel);
				break;
			case M_WHEEL_X:
				if(e.type == SDL_MOUSEWHEEL)
					m_cbAxisEvent.at(ptr)((float)e.wheel.x);
				break;
			case M_WHEEL_Y:
				if (e.type == SDL_MOUSEWHEEL)
					m_cbAxisEvent.at(ptr)((float)e.wheel.y);
				break;
			}
		}
	}
}

void ce::core::Input::unbindAllButtons()
{
	m_bUnbindButtons = true;
}

void ce::core::Input::unbindAllAxis()
{
	m_bUnbindAxis = true;
}