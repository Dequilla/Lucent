#include "Window.h"

ce::Window::Window(std::string title, int posx, int posy, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), posx, posy, width, height, SDL_WINDOW_OPENGL);
}

ce::Window::~Window()
{
	SDL_DestroyWindow(m_window);
}