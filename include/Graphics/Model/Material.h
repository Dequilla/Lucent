/**
* \file Material.h
*/
#pragma once

#include <vector>

#include "Graphics/Texture.h"
#include "Graphics/Shader/Shader.h"

namespace lu { namespace graphics {

	/**
	* \brief Material properties to describe some of what it needs to function
	*
	* TODO: Maybe move to shader?
	*/
	enum MaterialProperty
	{
		MAT_BLEND = 0x01	/**< Material should be blent with glBlend (contains opacity) */
	};

	/**
	* \brief Material representation
	*/
	struct Material
	{
		Shader shader; /**< Shader used to draw the material */
		
		std::vector<Texture> textures; /**< Textures used in this material */

		float shininess = 32.0f; /**< The shininess of the material */
		float opacity = 1.0f; /**< The opacity of the object */

		/**
		* \brief Checks if material has a property
		*/
		inline bool hasProperty(MaterialProperty matprop)
		{
			return ((m_materialProperties & matprop) ? true : false);
		}

	protected:
		friend class ModelLoader;

		unsigned int m_materialProperties = 0;
	};
	
}}