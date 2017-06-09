#pragma once

#include "SDL2/SDL.h"

#include <iostream>

namespace ce { namespace core { 

	class Application
	{
	public:

		void init();

		// Make this a singleton
		Application() {}
		static Application& getInstance();
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;

	protected:
		

	};

}}