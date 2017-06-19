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
	// Checks if a clear of binds has been requested and fullfills said request if
	unbindActual();

	// KEYBOARD/BUTTON EVENTS
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP || 
		e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ||
		e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)
	{
		try
		{
			for (auto &ptr : m_boundKeys)
			{
				// If key/button is pressed keyPressed = true
				bool keyPressed = (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONDOWN) ? true : false;

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

				// Controller buttons
				if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)
				{
					// Which controller
					SDL_JoystickID controllerID = e.cbutton.which;

					SDL_GameControllerButton button = (SDL_GameControllerButton)e.cbutton.button;
					
					switch (ptr)
					{
						// Right side buttons
					case C_BUTTON_FACE1:
						if(button == SDL_CONTROLLER_BUTTON_A)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_FACE2:
						if (button == SDL_CONTROLLER_BUTTON_X)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_FACE3:
						if (button == SDL_CONTROLLER_BUTTON_B)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_FACE4:
						if (button == SDL_CONTROLLER_BUTTON_Y)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;

						// DPAD / Left side buttons
					case C_BUTTON_DPAD_DOWN:
						if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_DPAD_UP:
						if (button == SDL_CONTROLLER_BUTTON_DPAD_UP)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_DPAD_LEFT:
						if (button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_DPAD_RIGHT:
						if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;

						// Stick left
					case C_BUTTON_STICK1:
						if (button == SDL_CONTROLLER_BUTTON_LEFTSTICK)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
						// Stick right
					case C_BUTTON_STICK2:
						if (button == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;

						// Back buttons
					case C_BUTTON_LBUMPER:
						if (button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_RBUMPER:
						if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;

						// Start / select
					case C_BUTTON_SELECT:
						if (button == SDL_CONTROLLER_BUTTON_BACK)
							m_cbButtonEvent.at(ptr)(keyPressed);
						break;
					case C_BUTTON_START:
						if (button == SDL_CONTROLLER_BUTTON_START)
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
	else if (e.type == SDL_MOUSEMOTION || 
			 e.type == SDL_MOUSEWHEEL ||
			 e.type == SDL_CONTROLLERAXISMOTION)
	{
		for (auto &ptr : m_boundAxis)
		{
			// MOUSE
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL)
			{
				switch (ptr)
				{
				case M_MOTION_X:
					if (e.type == SDL_MOUSEMOTION && e.motion.xrel != 0)
						m_cbAxisEvent.at(ptr)((float)e.motion.x);
					break;
				case M_MOTION_Y:
					if (e.type == SDL_MOUSEMOTION && e.motion.yrel != 0)
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
					if (e.type == SDL_MOUSEWHEEL)
						m_cbAxisEvent.at(ptr)((float)e.wheel.x);
					break;
				case M_WHEEL_Y:
					if (e.type == SDL_MOUSEWHEEL)
						m_cbAxisEvent.at(ptr)((float)e.wheel.y);
					break;
				}
			}
			// CONTROLLER AXIS
			else if (e.type == SDL_CONTROLLERAXISMOTION)
			{
				// Which controller
				SDL_JoystickID controllerID = e.caxis.which;

				SDL_GameControllerAxis caxis = (SDL_GameControllerAxis)e.caxis.axis;

				switch (ptr)
				{
					// LEFT STICK
				case C_AXIS_LSTICKX:
					if(e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;
				case C_AXIS_LSTICKY:
					if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;

					// RIGHT STICK
				case C_AXIS_RSTICKX:
					if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;
				case C_AXIS_RSTICKY:
					if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;

					// Triggers
				case C_AXIS_LTRIGGER:
					if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;
				case C_AXIS_RTRIGGER:
					if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
						m_cbAxisEvent.at(ptr)((float)e.caxis.value);
					break;
				}
			}
		}
	}
	// CONTROLLER EVENTS
	else if (e.type == SDL_CONTROLLERDEVICEADDED || e.type == SDL_CONTROLLERDEVICEREMOVED || SDL_CONTROLLERAXISMOTION)
	{
		switch (e.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			addController(e.cdevice.which);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			removeController(e.cdevice.which);
			break;
		}
	}
}

void ce::core::Input::clearButtonBinds()
{
	m_bUnbindButtons = true;
}

void ce::core::Input::clearAxisBinds()
{
	m_bUnbindAxis = true;
}

void ce::core::Input::addJoystick(int joystickID)
{
}

void ce::core::Input::addController(int controllerID)
{
	std::cout << "Joysticks/controllers connected: " << SDL_NumJoysticks() << std::endl;
	std::cout << "Controller ID: " << controllerID << std::endl;

	// TODO: if not a supported controller add support(test ps4?)
	if (SDL_IsGameController(controllerID))
	{
		Joystick controller;
		controller.controller = SDL_GameControllerOpen(controllerID);

		if (controller.controller)
		{
			
			controller.joystick = SDL_GameControllerGetJoystick(controller.controller);
			controller.instanceID = SDL_JoystickInstanceID(controller.joystick);

		}
		
	}
}

void ce::core::Input::removeController(int controllerID)
{
	Joystick controller;
	controller.controller = SDL_GameControllerFromInstanceID(controllerID);
	SDL_GameControllerClose(controller.controller);
}