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
				input.bindKeyboardEvent(K_0, this, &GameMode::TestTest);
				input.bindAxisEvent(M_MOTION_X, this, &GameMode::MouseX);
				input.bindAxisEvent(M_MOTION_Y, this, &GameMode::MouseY);
			}

			void MouseX(float movementX) { std::cout << "X: " << movementX << std::endl; }
			void MouseY(float movementY) { std::cout << "Y: " << movementY << std::endl; }
			void TestTest(bool key_pressed) { std::cout << "Key pressed: " << key_pressed << std::endl; }

		};

}} // End namespace