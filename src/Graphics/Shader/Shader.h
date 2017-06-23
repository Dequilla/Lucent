#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <unordered_map>

#include "GL/glew.h"
#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	// TODO: Add geometry shader
	class Shader
	{
	protected:
		unsigned int programID;

		// string is all paths appended to eachother
		static std::unordered_map<std::string, Shader> m_loadedShaders;

	public:
		Shader() {}
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

		void use(); // Set this shader program as current

		// Set uniforms in shader
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;

		void setVec2(const std::string &name, const glm::vec2 &value) const;
		void setVec2(const std::string &name, float x, float y) const;

		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec3(const std::string &name, float x, float y, float z) const;

		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setVec4(const std::string &name, float x, float y, float z, float w) const;

		void setMat2(const std::string &name, const glm::mat2& value) const;
		void setMat3(const std::string &name, const glm::mat3& value) const;
		void setMat4(const std::string &name, const glm::mat4& value) const;

	};

}}