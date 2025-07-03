#include "Core/Input.h"

void
lu::core::Input::unbindActual()
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

void
lu::core::Input::checkInput(const SDL_Event &e)
{
    // Checks if a clear of binds has been requested and fullfills said request
    // if
    unbindActual();

    // KEYBOARD/BUTTON EVENTS
    if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP ||
        e.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
        e.type == SDL_EVENT_MOUSE_BUTTON_UP ||
        e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
        e.type == SDL_EVENT_GAMEPAD_BUTTON_UP)
    {
        try
        {
            for (auto &ptr : m_boundKeys)
            {
                // If key/button is pressed keyPressed = true
                bool keyPressed = (e.type == SDL_EVENT_KEY_DOWN ||
                                   e.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
                                   e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN)
                                    ? true
                                    : false;

                // Check if it equals a key
                if (e.key.key == ptr)
                {
                    // Call callback function
                    m_cbButtonEvent.at(ptr)(keyPressed);
                }

                // Check if it is a mouse button
                if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
                    e.type == SDL_EVENT_MOUSE_BUTTON_UP)
                {
                    // If current bind we are checking equals any of the mouse
                    // buttons
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
                if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
                    e.type == SDL_EVENT_GAMEPAD_BUTTON_UP)
                {
                    // Which controller
                    SDL_JoystickID controllerID = e.gbutton.which;

                    SDL_GamepadButton button =
                      (SDL_GamepadButton)e.gbutton.button;

                    switch (ptr)
                    {
                            // Right side buttons
                        case C_BUTTON_FACE1:
                            if (button == SDL_GAMEPAD_BUTTON_SOUTH)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_FACE2:
                            if (button == SDL_GAMEPAD_BUTTON_WEST)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_FACE3:
                            if (button == SDL_GAMEPAD_BUTTON_EAST)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_FACE4:
                            if (button == SDL_GAMEPAD_BUTTON_NORTH)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;

                            // DPAD / Left side buttons
                        case C_BUTTON_DPAD_DOWN:
                            if (button == SDL_GAMEPAD_BUTTON_DPAD_DOWN)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_DPAD_UP:
                            if (button == SDL_GAMEPAD_BUTTON_DPAD_UP)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_DPAD_LEFT:
                            if (button == SDL_GAMEPAD_BUTTON_DPAD_LEFT)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_DPAD_RIGHT:
                            if (button == SDL_GAMEPAD_BUTTON_DPAD_RIGHT)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;

                            // Stick left
                        case C_BUTTON_STICK1:
                            if (button == SDL_GAMEPAD_BUTTON_LEFT_STICK)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                            // Stick right
                        case C_BUTTON_STICK2:
                            if (button == SDL_GAMEPAD_BUTTON_RIGHT_STICK)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;

                            // Back buttons
                        case C_BUTTON_LBUMPER:
                            if (button == SDL_GAMEPAD_BUTTON_LEFT_SHOULDER)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_RBUMPER:
                            if (button == SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;

                            // Start / select
                        case C_BUTTON_SELECT:
                            if (button == SDL_GAMEPAD_BUTTON_BACK)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                        case C_BUTTON_START:
                            if (button == SDL_GAMEPAD_BUTTON_START)
                                m_cbButtonEvent.at(ptr)(keyPressed);
                            break;
                    }
                }
            }
        }
        catch (std::exception &e)
        {
            lu::core::log(LU_AT,
                          "Exception in CheckInput: " + std::string(e.what()),
                          LOG_ERROR);
        }
    }
    // AXIS EVENTS
    else if (e.type == SDL_EVENT_MOUSE_MOTION ||
             e.type == SDL_EVENT_MOUSE_WHEEL ||
             e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION)
    {
        for (auto &ptr : m_boundAxis)
        {
            // MOUSE
            if (e.type == SDL_EVENT_MOUSE_MOTION ||
                e.type == SDL_EVENT_MOUSE_WHEEL)
            {
                switch (ptr)
                {
                    case M_MOTION_X:
                        if (e.type == SDL_EVENT_MOUSE_MOTION &&
                            e.motion.xrel != 0)
                            m_cbAxisEvent.at(ptr)((float)e.motion.x);
                        break;
                    case M_MOTION_Y:
                        if (e.type == SDL_EVENT_MOUSE_MOTION &&
                            e.motion.yrel != 0)
                            m_cbAxisEvent.at(ptr)((float)e.motion.y);
                        break;
                    case M_MOTION_XREL:
                        if (e.type == SDL_EVENT_MOUSE_MOTION &&
                            e.motion.xrel != 0)
                            m_cbAxisEvent.at(ptr)((float)e.motion.xrel);
                        break;
                    case M_MOTION_YREL:
                        if (e.type == SDL_EVENT_MOUSE_MOTION &&
                            e.motion.yrel != 0)
                            m_cbAxisEvent.at(ptr)((float)e.motion.yrel);
                        break;
                    case M_WHEEL_X:
                        if (e.type == SDL_EVENT_MOUSE_WHEEL)
                            m_cbAxisEvent.at(ptr)((float)e.wheel.x);
                        break;
                    case M_WHEEL_Y:
                        if (e.type == SDL_EVENT_MOUSE_WHEEL)
                            m_cbAxisEvent.at(ptr)((float)e.wheel.y);
                        break;
                }
            }
            // CONTROLLER AXIS
            else if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION)
            {
                // Which controller
                SDL_JoystickID controllerID = e.gaxis.which;

                SDL_GamepadAxis gaxis = (SDL_GamepadAxis)e.gaxis.axis;

                switch (ptr)
                {
                        // LEFT STICK
                    case C_AXIS_LSTICKX:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_LEFTX)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;
                    case C_AXIS_LSTICKY:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_LEFTY)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;

                        // RIGHT STICK
                    case C_AXIS_RSTICKX:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHTX)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;
                    case C_AXIS_RSTICKY:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHTY)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;

                        // Triggers
                    case C_AXIS_LTRIGGER:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;
                    case C_AXIS_RTRIGGER:
                        if (e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)
                            m_cbAxisEvent.at(ptr)((float)e.gaxis.value);
                        break;
                }
            }
        }
    }
    // CONTROLLER EVENTS
    else if (e.type == SDL_EVENT_GAMEPAD_ADDED ||
             e.type == SDL_EVENT_GAMEPAD_REMOVED ||
             SDL_EVENT_GAMEPAD_AXIS_MOTION)
    {
        switch (e.type)
        {
            case SDL_EVENT_GAMEPAD_ADDED:
                addController(e.cdevice.which);
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                removeController(e.cdevice.which);
                break;
        }
    }
}

void
lu::core::Input::clearButtonBinds()
{
    m_bUnbindButtons = true;
}

void
lu::core::Input::clearAxisBinds()
{
    m_bUnbindAxis = true;
}

void
lu::core::Input::addJoystick(int joystickID)
{
}

void
lu::core::Input::addController(int controllerID)
{
    if (SDL_IsGamepad(controllerID))
    {
        Joystick controller;
        controller.controller = SDL_OpenGamepad(controllerID);

        if (controller.controller)
        {
            controller.joystick = SDL_GetGamepadJoystick(controller.controller);
            controller.instanceID = SDL_GetJoystickID(controller.joystick);
        }
    }
}

void
lu::core::Input::removeController(int controllerID)
{
    Joystick controller;
    controller.controller = SDL_GetGamepadFromID(controllerID);
    SDL_CloseGamepad(controller.controller);
}
