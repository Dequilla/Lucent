#pragma once
#include <iostream>

// STB included in cpp

#include "GL/glew.h"

namespace ce { namespace graphics {

	enum TextureType
	{
		TEXTURE_DIFFUSE,
		TEXTURE_SPECULAR
	};

	struct Texture
	{
		// OpenGL texture ID
		unsigned int id;

		TextureType type;
	};

	unsigned int loadTexture(const char* path);

} }