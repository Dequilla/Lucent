#pragma once

#include <unordered_map>
#include <string>

#include "Shader.h"

namespace ce { namespace graphics {

	class ShaderManager {
	private:
		std::unordered_map<std::string, Shader> m_shaders;

	public:
		void addShader(std::string id, Shader shader);

		Shader getShader(std::string id);
		void removeShader(std::string id);
	};

}}