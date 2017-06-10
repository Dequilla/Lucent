#include "Application.h"

bool ce::core::Application::init()
{
	// Retrieve SDL_Versions
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	std::cout << "SDL_VERSION_COMPILED - " << (int)compiled.major << "." << (int)compiled.minor << "." << (int)compiled.patch << std::endl;
	std::cout << "SDL_VERSION_LINKED - " << (int)compiled.major << "." << (int)compiled.minor << "." << (int)compiled.patch << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "CE: Failed to initialize SDL with error:\n" << SDL_GetError() << std::endl;

		return false;
	}

	return true;
}

ce::core::Application& ce::core::Application::getInstance()
{
	static Application instance;
	return instance;
}