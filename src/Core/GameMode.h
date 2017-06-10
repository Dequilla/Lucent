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
				input.bindButtonEvent(K_w, this, &GameMode::TestTest);
				input.bindButtonEvent(K_a, this, &GameMode::TestTest);
				input.bindButtonEvent(K_s, this, &GameMode::TestTest);
				input.bindButtonEvent(K_d, this, &GameMode::TestTest);

				input.bindButtonEvent(M_BUTTON_MIDDLE, this, &GameMode::TestTest);

				input.bindAxisEvent(M_MOTION_XREL, this, &GameMode::MouseX);
				input.bindAxisEvent(M_MOTION_YREL, this, &GameMode::MouseY);
			}

			void MouseX(float movementX) { std::cout << "Relative X movement: " << movementX << std::endl; }
			void MouseY(float movementY) { std::cout << "Relative Y movement: " << movementY << std::endl; }
			void TestTest(bool key_pressed) { std::cout << "Button pressed: " << key_pressed << std::endl; }

		};

}} // End namespace