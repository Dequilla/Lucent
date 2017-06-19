#pragma once

#include "SDL2/SDL.h"

#include <iostream>

namespace ce { namespace core { 

	class Application
	{
	protected:
	public:

		int screenWidth = 0;
		int screenHeight = 0;

		// Has to be called before anything else in the application
		bool init();

		// Is a singleton
		Application() {}
		static Application& getInstance();
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;
	};

}}