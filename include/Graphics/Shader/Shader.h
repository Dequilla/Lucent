/**
* \file Shader.h
* \brief Contains the shader object
*/
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <unordered_map>

#include "GL/glew.h"
#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	/**
	* \brief Shader class mostly a container for the id and contains some helper functions
	* 
	* TODO: Add geometry shader
	*/
	class Shader
	{
	protected:
		friend class ShaderLoader;

		unsigned int programID; /**< OpenGL shader program ID */

	public:
		Shader() {}

		void use(); /**< Use this shader program */
		unsigned int getProgramID() const { return programID; }

		void setBool(const std::string &name, bool value) const;	/**< Set shader uniform bool */
		void setInt(const std::string &name, int value) const;		/**< Set shader uniform int */
		void setFloat(const std::string &name, float value) const;	/**< Set shader uniform float */

		void setVec2(const std::string &name, const glm::vec2 &value) const;	/**< Set shader uniform 2 component vector */
		void setVec2(const std::string &name, float x, float y) const;			/**< Set shader uniform 2 component vector */

		void setVec3(const std::string &name, const glm::vec3 &value) const;	/**< Set shader uniform 3 component vector */
		void setVec3(const std::string &name, float x, float y, float z) const;	/**< Set shader uniform 3 component vector */

		void setVec4(const std::string &name, const glm::vec4 &value) const;				/**< Set shader uniform 4 component vector */
		void setVec4(const std::string &name, float x, float y, float z, float w) const;	/**< Set shader uniform 4 component vector */

		void setMat2(const std::string &name, const glm::mat2& value) const;	/**< Set shader uniform 2d matrix */
		void setMat3(const std::string &name, const glm::mat3& value) const;	/**< Set shader uniform 3d matrix */
		void setMat4(const std::string &name, const glm::mat4& value) const;	/**< Set shader uniform 4d matrix */
	};
}}