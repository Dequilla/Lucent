#pragma once

#include "SDL2/SDL.h"

#include <iostream>

namespace ce { namespace core { 

	class Application
	{
	public:

		// Has to be called before anything else in the application
		bool init();

		// Make this a singleton
		Application() {}
		static Application& getInstance();
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;

	protected:
		

	};

}}