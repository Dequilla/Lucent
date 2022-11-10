/**
* \file Texture.h
*
* Some smaller utility for textures:
*  - Loading textures
*  - Texture type definition
*/

#pragma once
#include <iostream>

// STB included in cpp

#include "GL/glew.h"

#include "Core/Utility/log.h"

namespace ce { namespace graphics {

	/**
	* \brief What the texture will be used for
	*/
	enum TextureType
	{
		TEXTURE_DIFFUSE, /**< Texture will be used for diffuse mapping */
		TEXTURE_SPECULAR /**< Texture will be used for specular mapping */
	};

	/**
	* \brief A structure describing a texture
	*/
	struct Texture
	{
		unsigned int id; /**< Texture id internally of OpenGL */

		TextureType type;	/**< The texture type used to determine what kind of texture this is */
	};

	/**
	* \brief Load a texture for use in OpenGL
	* @param path Path to texture
	* @return unsigned int which is the id for use in OpenGL
	*/
	unsigned int loadTexture(const char* path);

} }