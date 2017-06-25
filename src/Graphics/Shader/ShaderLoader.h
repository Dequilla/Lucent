#pragma once

#include <unordered_map>
#include <vector>

#include "Core/Utility/stringutility.h"
#include "Core/Utility/log.h"

#include "Graphics/Shader/Shader.h"

namespace ce { namespace graphics {

	struct ShaderProperties
	{
		std::string vPath = "";
		std::string fPath = "";
		std::string gPath = ""; // TODO

		unsigned int numDirLights = 0;
		unsigned int numPointLights = 0;
		unsigned int numSpotLights = 0;

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

	class ShaderLoader
	{
	protected:
		static std::vector<std::pair<ShaderProperties, Shader>> m_loadedShaders;

		Shader loadFromSource(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySourc = "");

	public:
		ShaderLoader() {}
		~ShaderLoader() {}

		Shader* loadShader(ShaderProperties properties);

		// Check if a shader with ShaderProperties exist already
		bool alreadyExists(ShaderProperties properties);
	};

}}
