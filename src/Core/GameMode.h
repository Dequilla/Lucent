#pragma once

#include <iostream>

#include "Core/Input.h"

namespace ce
{
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
			input.bindKeypress(K_0, this, &GameMode::Test); 
			input.bindKeypress(K_0, this, &GameMode::TestTest);
		}


		void Test() { std::cout << "TEST" << std::endl; }
		void TestTest() { std::cout << "TEST TEST WOOO" << std::endl; }

	};

}