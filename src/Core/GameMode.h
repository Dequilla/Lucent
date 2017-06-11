#pragma once

#include <iostream>

#include "Core/Input.h"

namespace ce { namespace core {

		// TODO: Current version of this is extremely temporary to test INPUT methods
		class GameMode
		{
		protected:

		public:

			Input input;

			void checkInput(const SDL_Event &e)
			{
				input.checkInput(e);
			}

			GameMode()
			{
				input.bindButtonEvent(K_ESCAPE, this, &GameMode::clearBind);
			}

			void clearBind(bool key_pressed) 
			{ 
				std::cout << "Clearing bind" << std::endl;
				input.unbindAllButtons();
			}
		};

}} // End namespace