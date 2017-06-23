#pragma once

#include <vector>

#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoord;
	};

	typedef std::vector<Vertex> VertexArray;
	typedef std::vector<unsigned int> IndexArray;

}}