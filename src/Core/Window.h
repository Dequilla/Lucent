#include "SDL2/SDL.h" 

#include <string>

namespace ce
{
	class Window
	{
	protected:
		SDL_Window* m_window;

	public:
		Window(std::string title, int posx, int posy, int width, int height);
		~Window();
	};
}