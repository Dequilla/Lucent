/**
 * \file Input.h
 */
#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "SDL2/SDL.h"

#include "Core/Utility/log.h"

#include "InputCodes.h"

namespace lu
{
    namespace core
    {

        /**
         * \struct Joystick
         * \brief Structure containing information needed for Joysticks and
         * Controllers
         */
        struct Joystick
        {
                int instanceID = 0;
                SDL_Joystick *joystick = nullptr;
                SDL_GameController *controller = nullptr;
        };

        /**
         * \brief Class for handling user input
         *
         * Class for handling user input through a callback system.
         */
        class Input
        {
            private:
                std::unordered_map<int, std::function<void(bool)>>
                  m_cbButtonEvent;
                std::vector<KeyCodes> m_boundKeys;

                std::unordered_map<int, std::function<void(float)>>
                  m_cbAxisEvent;
                std::vector<AxisEventCodes> m_boundAxis;

                void unbindActual();
                bool m_bUnbindButtons = false;
                bool m_bUnbindAxis = false;

                void addJoystick(int joystickID);
                void addController(int controllerID);
                void removeController(int controllerID);

            public:
                void checkInput(
                  const SDL_Event &e); /**< Polls input and calls callbacks */

                void
                clearButtonBinds(); /**< Completely clear the button bindings */
                void
                clearAxisBinds(); /**< Completely clear the axis bindings */

                /**
                 * \brief Register a button event to a callback
                 *
                 * @param key Keycode to identify callback with
                 * @param instance Class instance which contains the function
                 * @param func A function pointer, function must have a bool
                 * parameter and returntype void (eg: &AClass::Function)
                 */
                template<class T>
                void bindButtonEvent(KeyCodes key,
                                     T *instance,
                                     void (T::*func)(bool));

                /**
                 * \brief Register a axis event to a callback
                 *
                 * @param key AxisEventCode to identify callback with
                 * @param instance Class instance which contains the function
                 * @param func A function pointer, function must have a float
                 * parameter and returntype void (eg: &AClass::Function)
                 */
                template<class T>
                void bindAxisEvent(AxisEventCodes axis,
                                   T *instance,
                                   void (T::*func)(float));
        };

        template<class T>
        inline void lu::core::Input::bindButtonEvent(KeyCodes key,
                                                     T *instance,
                                                     void (T::*func)(bool))
        {
            // Remove any already bound references
            for (unsigned int i = 0; i < m_boundKeys.size(); i++)
            {
                // Already bound
                if (m_boundKeys.at(i) == key)
                {
                    m_boundKeys.erase(m_boundKeys.begin() + i);

                    // This means there	is a duplicate in our map, erase it
                    m_cbButtonEvent.erase(key);
                }
            }

            // Bind new reference
            auto callback = std::bind(
              func,
              instance,
              std::placeholders::_1); // NOTE: Never forget placeholders if
                                      // have arguments
            m_cbButtonEvent.emplace(key, callback);
            m_boundKeys.push_back(key);
        }

        template<class T>
        inline void lu::core::Input::bindAxisEvent(AxisEventCodes axis,
                                                   T *instance,
                                                   void (T::*func)(float))
        {
            // Remove any already bound references
            for (unsigned int i = 0; i < m_boundAxis.size(); i++)
            {
                // Already bound
                if (m_boundAxis.at(i) == axis)
                {
                    m_boundAxis.erase(m_boundAxis.begin() + i);

                    // This means there	is a duplicate in our map, erase it
                    m_cbAxisEvent.erase(axis);
                }
            }

            // Bind new reference
            auto callback = std::bind(
              func,
              instance,
              std::placeholders::_1); // NOTE: Never forget placeholders if
                                      // have arguments
            m_cbAxisEvent.emplace(axis, callback);
            m_boundAxis.push_back(axis);
        }

    }
} // Namespace end