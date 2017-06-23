#pragma once

#include <vector>

#include "Graphics/Texture.h"
#include "Graphics/Shader/Shader.h"

namespace ce { namespace graphics {

	struct Material
	{
		Shader shader;
		
		std::vector<Texture> textures;

		float shininess = 32.0f; // Specular shininess

		float opacity = 1.0f; // For transparency
	};
	
}}