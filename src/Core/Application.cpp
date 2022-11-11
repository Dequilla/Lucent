#include "Core/Application.h"

glm::vec2 lu::core::Application::getScreenBufferSizeInternal()
{
	glm::vec2 size;
	size.x = getInstance().m_screenWidth;
	size.y = getInstance().m_screenHeight;

	return size;
}

void lu::core::Application::setScreenBufferSizeInternal(glm::vec2 screenSize)
{
	getInstance().m_screenWidth = screenSize.x;
	getInstance().m_screenHeight = screenSize.y;
}

void lu::core::Application::setScreenBufferSizeInternal(unsigned int width, unsigned int height)
{
	getInstance().m_screenWidth = width;
	getInstance().m_screenHeight = height;
}

bool lu::core::Application::initInternal()
{
	// Retrieve SDL_Versions
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	std::string compiledVersion = "SDL_VERSION_COMPILED - " + std::to_string((int)compiled.major) + "." + std::to_string((int)compiled.minor) + "." + std::to_string((int)compiled.patch);
	std::string linkedVersion = "SDL_VERSION_LINKED - " + std::to_string((int)compiled.major) + "." + std::to_string((int)compiled.minor) + "." + std::to_string((int)compiled.patch);

	lu::core::log(compiledVersion);
	lu::core::log(linkedVersion);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		lu::core::log(LU_AT, "Failed to initialize SDL with error:\n" + std::string(SDL_GetError()), LOG_ERROR);
		return false;
	}

	// Initialize text
	if (lu::graphics::initText())
	{
		return false;
	}

	return true;
}

void lu::core::Application::enableVSYNCInternal(bool enabled)
{
	SDL_GL_SetSwapInterval(((enabled) ? 1 : 0));
}

glm::vec2 lu::core::Application::getScreenBufferSize()
{
	return getInstance().getScreenBufferSizeInternal();
}

void lu::core::Application::setScreenBufferSize(glm::vec2 size)
{
	getInstance().setScreenBufferSizeInternal(size);
}

void lu::core::Application::setScreenBufferSize(unsigned int w, unsigned int h)
{
	getInstance().setScreenBufferSizeInternal(w, h);
}

bool lu::core::Application::init()
{
	return getInstance().initInternal();
}

void lu::core::Application::enableVSYNC(bool enabled)
{
	getInstance().enableVSYNCInternal(enabled);
}

lu::core::Application& lu::core::Application::getInstance()
{
	static Application instance;
	return instance;
}