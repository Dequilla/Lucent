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
				input.bindButtonEvent(C_BUTTON_LBUMPER, this, &GameMode::buttonWorks1);
			
				input.bindAxisEvent(C_AXIS_LTRIGGER, this, &GameMode::X);
				input.bindAxisEvent(C_AXIS_RTRIGGER, this, &GameMode::Y);

			}

			void buttonWorks1(bool key_pressed)
			{
				std::cout << "Button works 1" << std::endl;
			}
			void X(float x)
			{
				std::cout << "X: " << x << std::endl;
			}
			void Y(float y)
			{
				std::cout << "Y: " << y << std::endl;
			}
		};

}} // End namespace