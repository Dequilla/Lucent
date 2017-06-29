/**
* \file Application.h
*/
#pragma once

#include "SDL2/SDL.h"

#include "Core/Utility/log.h"

#include <iostream>
#include <string>

namespace ce { namespace core { 

	/**
	* \brief Application singlton containing context info needed by some components.
	*
	* Application singlton containing context info needed by some components
	* such as screen width and screen height.
	*/
	class Application
	{
	protected:
	public:

		int screenWidth = 0; /**< Screen buffer width for desired output */
		int screenHeight = 0; /**< Screen buffer height for desired output */

		bool init(); /**< Initializes some of the libraries used internally, called by the engine first thing that happens */

		// Is a singleton
		Application() {}
		static Application& getInstance();
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;
	};

}}