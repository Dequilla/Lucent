#include "Application.h"

bool ce::core::Application::init()
{
	// Retrieve SDL_Versions
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	std::string compiledVersion = "SDL_VERSION_COMPILED - " + std::to_string((int)compiled.major) + "." + std::to_string((int)compiled.minor) + "." + std::to_string((int)compiled.patch);
	std::string linkedVersion = "SDL_VERSION_LINKED - " + std::to_string((int)compiled.major) + "." + std::to_string((int)compiled.minor) + "." + std::to_string((int)compiled.patch);

	ce::core::log(compiledVersion);
	ce::core::log(linkedVersion);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		ce::core::log("CE: Failed to initialize SDL with error:\n" + std::string(SDL_GetError()), LOG_ERROR);
		return false;
	}

	return true;
}

ce::core::Application& ce::core::Application::getInstance()
{
	static Application instance;
	return instance;
}