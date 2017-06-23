#pragma once
#include <string>
#include <iostream>

#include "GLM/glm.hpp"
#include "SDL2/SDL.h" 
#include "GL/glew.h"


namespace ce { namespace core {

	enum WindowFlags
	{
		WINDOW_FULLSCREEN			= SDL_WINDOW_FULLSCREEN,			/* Fullscreen window */
		WINDOW_FULLSCREEN_DESKTOP	= SDL_WINDOW_FULLSCREEN_DESKTOP,	/* Fullscreen window at the current desktop resolution*/
		WINDOW_SHOWN				= SDL_WINDOW_SHOWN,					/* Window is visible (default) */	
		WINDOW_HIDDEN				= SDL_WINDOW_HIDDEN,				/* Window is hidden */
		WINDOW_RESIZABLE			= SDL_WINDOW_RESIZABLE,				/* Window is resizeable */
		WINDOW_BORDERLESS			= SDL_WINDOW_BORDERLESS,			/* Window has no decorations */
		WINDOW_MINIMIZED			= SDL_WINDOW_MINIMIZED,				/* Window opens minimized */
		WINDOW_MAXAMIZED			= SDL_WINDOW_MAXIMIZED,				/* Window opens maxamized */
	};

	// Used to indicate that the window should be centered
	const unsigned int WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;

	class Window
	{
	protected:
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_glContext = NULL;

		void initVideoComponents();
		void destroyWindow();

	public:
		Window() {}
		Window(std::string title, int posx, int posy, int width, int height, unsigned int flags = WINDOW_SHOWN);
		~Window();

		void create(std::string title, int posx, int posy, int width, int height, unsigned int flags = WINDOW_SHOWN);

		void setClearColor(float r, float g, float b, float a = 0.0f);
		void clear();
		void display();

		void setSize(int width, int height);

		void setTitle(std::string title);
		void setWindowGrab(bool grab);
		void setWindowFullscreen(unsigned int type); // WINDOW_FULLSCREEN, WINDOW_FULLSCREEN_DESKTOP or 0

		glm::vec2 getSize();
	};

}} // Namespace end