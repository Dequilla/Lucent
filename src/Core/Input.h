#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "SDL2/SDL.h"

#include "Keycodes.h"

namespace ce
{

	class Input
	{
	protected:
		std::unordered_map<KeyCodes, std::function< void() >> m_cbKeypress; // Map with callbacks
		std::vector<KeyCodes> m_boundKeys; // Used to determine which keys to check

		// Todo add axis support, mouse, joystick, controller

	public:
		
		// TODO: reconsider where we do the event polling and how we interact with events
		// TODO: Check if controller buttons, joystickbuttons and mouse buttons work
		void checkInput(const SDL_Event &e);

		// Bind a function to a keypress
		// If bind to a key already bound to, you replace that binding in this input module
		// Param 1: KeyCode that it reacts to
		// Param 2: The instance of which contains the function
		// Param 3: The function itself (eg: &AClass::Function)
		template <class T>
		void bindKeypress(KeyCodes key, T* instance, void(T::* func)());
	};

	template<class T>
	inline void ce::Input::bindKeypress(KeyCodes key, T* instance, void(T::* func)())
	{
		// Remove any already bound references
		for (unsigned int i = 0; i < m_boundKeys.size(); i++)
		{
			// Already bound
			if (m_boundKeys.at(i) == key)
			{
				m_boundKeys.erase(m_boundKeys.begin() + i);

				// This means there should be a duplicate in our map aswell
				m_cbKeypress.erase(key);
			}
		}

		auto callback = std::bind(func, instance);
		m_cbKeypress.emplace(key, callback);
		m_boundKeys.push_back(key);
	}

}