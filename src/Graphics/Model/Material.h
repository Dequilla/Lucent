#pragma once

#include <vector>

#include "Graphics/Texture.h"
#include "Graphics/Shader/Shader.h"

namespace ce { namespace graphics {

	// TODO:
	// ASSIMP: BLEND_FUNC to determine if we blend it (if we have textures with opacity or opacity isnt 1.0f
	// AssimpMaterial.Get()
	// Material goal:
	//  - Diffuse color
	//  - Specular color
	//  - Ambient color
	//  - Emissive color (Maybe, but later?)
	//  - Global Opacity (transparency for whole mesh)
	//  - Shininess
	//  - Diffuse mapping (Can contain transparency, sample transparency from this texture)
	//  - Specular mapping
	//  When all these are supported and stable:
	//  - Normal mapping etc.

	struct Material
	{
		Shader shader;
		
		std::vector<Texture> textures;

		float shininess = 32.0f; // Specular shininess

		float opacity = 1.0f; // For transparency
	};
	
}}