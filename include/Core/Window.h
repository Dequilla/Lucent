/**
* \file Window.h
*/
#pragma once

#include <string>
#include <iostream>

#include "GLM/glm.hpp"
#include "SDL2/SDL.h" 
#include "GL/glew.h"

#include "Core/Utility/log.h"


namespace ce { namespace core {

	/**
	* \enum
	* \brief Flags describing how the window should be created
	*/
	enum WindowFlags
	{
		WINDOW_FULLSCREEN			= SDL_WINDOW_FULLSCREEN,			/**< Fullscreen window */
		WINDOW_FULLSCREEN_DESKTOP	= SDL_WINDOW_FULLSCREEN_DESKTOP,	/**< Fullscreen window at the current desktop resolution*/
		WINDOW_SHOWN				= SDL_WINDOW_SHOWN,					/**< Window is visible (default) */	
		WINDOW_HIDDEN				= SDL_WINDOW_HIDDEN,				/**< Window is hidden */
		WINDOW_RESIZABLE			= SDL_WINDOW_RESIZABLE,				/**< Window is resizeable */
		WINDOW_BORDERLESS			= SDL_WINDOW_BORDERLESS,			/**< Window has no decorations */
		WINDOW_MINIMIZED			= SDL_WINDOW_MINIMIZED,				/**< Window opens minimized */
		WINDOW_MAXAMIZED			= SDL_WINDOW_MAXIMIZED,				/**< Window opens maxamized */
	};

	/**
	* \var WINDOWPOS_CENTERED
	* \brief Constant used to set window position centered
	*/
	const unsigned int WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;

	/**
	* \brief A window class that can be drawn to
	*/
	class Window
	{
	protected:
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_glContext = NULL;

		void initVideoComponents();
		void destroyWindow();

	public:
		Window() {}

		/**
		* \brief Constructor for creating the window
		*
		* @param title Window title
		* @param posx Window position x on screen (WINDOWPOS_CENTERED for centered)
		* @param posy Window position y on screen (WINDOWPOS_CENTERED for centered)
		* @param width Window width
		* @param height Window height
		* @param flags WindowFlags describing how the window should be created
		*/
		Window(std::string title, int posx, int posy, int width, int height, unsigned int flags = WINDOW_SHOWN);
		~Window();

		/**
		* \brief Function for creating the window
		*
		* @param title Window title
		* @param posx Window position x on screen (WINDOWPOS_CENTERED for centered)
		* @param posy Window position y on screen (WINDOWPOS_CENTERED for centered)
		* @param width Window width
		* @param height Window height
		* @param flags WindowFlags describing how the window should be created
		*/
		void create(std::string title, int posx, int posy, int width, int height, unsigned int flags = WINDOW_SHOWN);

		/**
		* \breif Sets the clearcolor for this window and its context
		*
		* @param r Red component (0.0f - 1.0f)
		* @param g Green component (0.0f - 1.0f)
		* @param b Blue component (0.0f - 1.0f)
		* @param a Alpha component (0.0f - 1.0f)
		*/
		void setClearColor(float r, float g, float b, float a = 0.0f);

		void clear(); /**< Clears window buffer with the set clear color */
		void display(); /**< Changes buffer behind the scene essentially displaying all that has been rendered */

		/**
		* \brief Sets the window size
		*
		* @param width Width
		* @param height Height
		*/
		void setSize(int width, int height);

		/**
		* \brief Sets the window title
		*
		* @param title Title
		*/
		void setTitle(std::string title);

		/**
		* \brief Sets the window grab
		*
		* Essentially tell the window to hide the cursor and keep it inside the bounds of the window.
		*
		* @param grab Decides if window should grab the cursor or not
		*/
		void setWindowGrab(bool grab);

		/**
		* \brief Set fullscreen mode
		*
		* @param type Should be either WINDOW_FULLSCREEN, WINDOW_FULLSCREEN_DESKTOP or 0 to set back to windowed
		*/
		void setWindowFullscreen(unsigned int type);

		glm::vec2 getSize(); /**< Returns a vector with the width and height of the window */
	};

}} // Namespace end