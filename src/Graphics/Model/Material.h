#pragma once

#include <vector>

#include "Graphics/Texture.h"
#include "Graphics/Shader/Shader.h"

namespace ce { namespace graphics {

	enum MaterialProperty
	{
		MAT_BLEND = 0x01
	};

	struct Material
	{
		Shader* shader;
		
		std::vector<Texture> textures;

		float shininess = 32.0f;
		float opacity = 1.0f;

		inline bool hasProperty(MaterialProperty matprop)
		{
			return ((m_materialProperties & matprop) ? true : false);
		}

	protected:
		friend class ModelLoader;

		unsigned int m_materialProperties = 0;
	};
	
}}