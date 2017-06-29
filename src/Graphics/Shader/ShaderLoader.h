/**
* \file ShaderLoader.h
*
* Contains functionality for loading shaders
*/
#pragma once

#include <unordered_map>
#include <vector>

#include "Core/Utility/stringutility.h"
#include "Core/Utility/log.h"

#include "Graphics/Shader/Shader.h"

namespace ce { namespace graphics {

	/**
	* \brief ShaderProperty structure describing what a shader should contain
	*/
	struct ShaderProperties
	{
		std::string vPath = "";	/**< Vertex shader path	  */
		std::string fPath = ""; /**< Fragment shader path */
		std::string gPath = ""; /**< Geometry shader path */

		unsigned int numDirLights = 0;	 /**< Number of directional lights it needs to support */
		unsigned int numPointLights = 0; /**< Number of point lights it needs to support */
		unsigned int numSpotLights = 0; /**< Number of spot lights it needs to support */

		/**
		* \breif Comparison operator definition
		*/
		bool operator==(const ShaderProperties& other) const
		{
			return
			(
				vPath == other.vPath &&
				fPath == other.fPath &&
				gPath == other.gPath &&
				numDirLights == other.numDirLights &&
				numPointLights == other.numPointLights &&
				numSpotLights == other.numSpotLights
			);
		}
	};

	/**
	* \brief Class used to load shaders
	*
	* Together with shader properties we make sure we only ever load a shader with the same properties once.
	*/
	class ShaderLoader
	{
	private:
		static std::vector<std::pair<ShaderProperties, Shader>> m_loadedShaders;

	protected:
		/**
		* \brief compiles shader code into a program and returns the shader
		*
		* @param vertexSource The source code for the vertex shader
		* @param fragmentSource The source code for the fragment shader
		* @param geometrySource The source code for the geometry shader (Yet to be implemented)
		* @return Shader program object.
		*/
		Shader loadFromSource(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = "");

	public:
		ShaderLoader() {}
		~ShaderLoader() {}

		/**
		* \breif Load shader with shader properties
		*
		* @param properties ShaderProperties describing the shader 
		* @return Pointer to shader program object
		*/
		Shader* loadShader(ShaderProperties properties);

		/**
		* \breif Check if a shader with ShaderProperties has been loaded previously
		*
		* @param properties ShaderProperties describing the shader
		* @return True if it has been loaded, false if not
		*/
		bool alreadyExists(ShaderProperties properties);
	};

}}
