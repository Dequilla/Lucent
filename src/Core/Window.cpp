#include "Core/Window.h"

void ce::core::Window::initVideoComponents()
{
	// Set openGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void ce::core::Window::destroyWindow()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_glContext);
}

ce::core::Window::Window(std::string title, int posx, int posy, int width, int height, unsigned int flags)
{
	create(title, posx, posy, width, height, flags);
}

ce::core::Window::~Window()
{
	destroyWindow();
}

void ce::core::Window::create(std::string title, int posx, int posy, int width, int height, unsigned int flags)
{
	initVideoComponents();

	if(m_window != nullptr || m_window != NULL && m_glContext != nullptr || m_glContext != NULL)
	{
		destroyWindow();
	}

	// Create the window
	m_window = SDL_CreateWindow(title.c_str(), posx, posy, width, height, SDL_WINDOW_OPENGL | flags);
	if (m_window == NULL)
	{
		ce::core::log(CE_AT, "Failed to create window with title: " + title + " with error: " + SDL_GetError(), LOG_ERROR);
	}

	// Create the context
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == NULL)
	{
		ce::core::log(CE_AT, "Failed to create a GL context for the window with the title: " + title + " with error: " + SDL_GetError(), LOG_ERROR);
	}
	SDL_GL_MakeCurrent(m_window, m_glContext);

	// Need a context to init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		ce::core::log(CE_AT, "GLEW failed to initialize", LOG_ERROR);
	}
}

void ce::core::Window::setClearColor(float r, float g, float b, float a)
{
	if (m_glContext != SDL_GL_GetCurrentContext())
	{
		SDL_GL_MakeCurrent(m_window, m_glContext);
	}

	glClearColor(r, g, b, a);
}

void ce::core::Window::clear()
{
	if (m_glContext != SDL_GL_GetCurrentContext())
	{
		SDL_GL_MakeCurrent(m_window, m_glContext);
	}

	glClear(GL_COLOR_BUFFER_BIT);
}

void ce::core::Window::display()
{
	SDL_GL_SwapWindow(m_window);
}

void ce::core::Window::setSize(int width, int height)
{
	SDL_SetWindowSize(m_window, width, height);
}

void ce::core::Window::setTitle(std::string title)
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void ce::core::Window::setWindowGrab(bool grab)
{
	SDL_SetRelativeMouseMode((grab) ? SDL_TRUE : SDL_FALSE);
}

void ce::core::Window::setWindowFullscreen(unsigned int type)
{
	SDL_SetWindowFullscreen(m_window, type);
}

glm::vec2 ce::core::Window::getSize()
{
	int width, height;
	SDL_GetWindowSize(m_window, &width, &height);
	return glm::vec2(width, height);
}
