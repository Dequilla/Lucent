#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "SDL2/SDL.h"

#include "InputCodes.h"

namespace ce { namespace core {

	class Input
	{
	protected:
		// Bound Keyboard callbacks get with them a bool (true = key_pressed, false = key_released)
		std::unordered_map<int, std::function< void(bool) >> m_cbKeyboardEvent;
		std::vector<KeyCodes> m_boundKeys;
		// TODO TODO: Add mouse buttons to keys (dont even need to add it to keycodes, just create new ones and handle seperatly MAYBE will need it compatible with keycodes doe)

		// Bound Axis callbacks get with them their axis value (eg: mouse position)
		std::unordered_map<int, std::function< void(float) >> m_cbAxisEvent;
		std::vector<AxisEventCodes> m_boundAxis;

	public:
		// TODO: reconsider where we do the event polling and how we interact with events
		void checkInput(const SDL_Event &e);

		// Bind a function to a keypress
		// Param 1: KeyCode that it reacts to
		// Param 2: The instance which contains the function
		// Param 3: The function itself (eg: &AClass::Function)
		template <class T>
		void bindKeyboardEvent(KeyCodes key, T* instance, void(T::*func)(bool));

		// Bind a function to a axis event like the mouse
		// Param 1: Axis it reacts to
		// Param 2: The instance which contains the function
		// Param 3: The function itself (eg: &AClass::Function)
		template <class T>
		void bindAxisEvent(AxisEventCodes axis, T* instance, void(T::*func)(float));
	};

	template<class T>
	inline void ce::core::Input::bindKeyboardEvent(KeyCodes key, T* instance, void(T::*func)(bool))
	{
		// Remove any already bound references
		for (unsigned int i = 0; i < m_boundKeys.size(); i++)
		{
			// Already bound
			if (m_boundKeys.at(i) == key)
			{
				m_boundKeys.erase(m_boundKeys.begin() + i);

				// This means there	is a duplicate in our map, erase it
				m_cbKeyboardEvent.erase(key);
			}
		}

		// Bind new reference
		auto callback = std::bind(func, instance, std::placeholders::_1); // NOTE: Never forget placeholders if have arguments
		m_cbKeyboardEvent.emplace(key, callback);
		m_boundKeys.push_back(key);
	}

	template<class T>
	inline void ce::core::Input::bindAxisEvent(AxisEventCodes axis, T * instance, void(T::* func)(float))
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
		auto callback = std::bind(func, instance, std::placeholders::_1); // NOTE: Never forget placeholders if have arguments
		m_cbAxisEvent.emplace(axis, callback);
		m_boundAxis.push_back(axis);
	}

}} // Namespace end