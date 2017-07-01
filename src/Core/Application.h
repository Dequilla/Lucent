/**
* \file Application.h
*/
#pragma once

#include "SDL2/SDL.h"

#include "GLM/glm.hpp"

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
		glm::vec2 getScreenBufferSizeInternal();
		void setScreenBufferSizeInternal(glm::vec2 screenSize);
		void setScreenBufferSizeInternal(unsigned int width, unsigned int height);

		int m_screenWidth = 0; /**< Screen buffer width for desired output */
		int m_screenHeight = 0; /**< Screen buffer height for desired output */

		bool initInternal();

	public:
		static glm::vec2 getScreenBufferSize();
		static void setScreenBufferSize(glm::vec2 size);
		static void setScreenBufferSize(unsigned int w, unsigned int h);

		static bool init(); /**< Initializes some of the libraries used internally, called by the engine first thing that happens */

		// Is a singleton
		Application() {}
		static Application& getInstance();
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;
	};

}}