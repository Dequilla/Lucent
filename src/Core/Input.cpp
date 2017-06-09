#include "Input.h"

void ce::Input::checkInput(const SDL_Event & e)
{
	// Iterate all the bound keys
	for (auto &ptr : m_boundKeys)
	{
		// If the current key is equal to the bound key
		if (e.key.keysym.sym == ptr)
		{
			// Call callback function
			m_cbKeypress.at(ptr)();
		}
	}
}