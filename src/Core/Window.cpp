#include "Window.h"

bool ce::Window::initVideoComponents()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "CE: Failed to initialize SDL with error:\n" << SDL_GetError() << std::endl;
		
		return false;
	}

	// Set openGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

ce::Window::Window(std::string title, int posx, int posy, int width, int height, unsigned int flags)
{
	// Initialize any videocomponents we will need
	initVideoComponents();

	// Create the window
	m_window = SDL_CreateWindow(title.c_str(), posx, posy, width, height, SDL_WINDOW_OPENGL | flags);
	if (m_window == NULL)
	{
		std::cout << "CE: Failed to create window with title: "
			<< title << " containing error: " << SDL_GetError() << std::endl;
	}

	// Create the context
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == NULL)
	{
		std::cout << "CE: Failed to create a GL context for the window with the title: "
					<< title << " containing error:\n" << SDL_GetError() << std::endl;
	}

	// Need a context to init GLEW
	glewExperimental = GL_TRUE;
	glewInit();
}

ce::Window::~Window()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_glContext);
}

void ce::Window::setClearColor(float r, float g, float b, float a)
{
	if (m_glContext != SDL_GL_GetCurrentContext())
	{
		SDL_GL_MakeCurrent(m_window, m_glContext);
	}

	glClearColor(r, g, b, a);
}

void ce::Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void ce::Window::display()
{
	SDL_GL_SwapWindow(m_window);
}

void ce::Window::setSize(int width, int height)
{
	SDL_SetWindowSize(m_window, width, height);
}

void ce::Window::setResizeable(bool x)
{
	SDL_SetWindowResizable(m_window, (SDL_bool)x);
}

void ce::Window::setTitle(std::string title)
{
	SDL_SetWindowTitle(m_window, title.c_str());
}