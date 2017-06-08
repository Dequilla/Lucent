#include "SDL2/SDL.h" 
#include "GL/glew.h"

#include <string>
#include <iostream>

namespace ce
{
	class Window
	{
	protected:
		SDL_Window* m_window;
		SDL_GLContext m_glContext;

		bool initVideoComponents();

	public:
		Window(std::string title, int posx, int posy, int width, int height);
		~Window();

		void setClearColor(float r, float g, float b, float a = 0.0f);
		void clear();
		void display();
	};
}