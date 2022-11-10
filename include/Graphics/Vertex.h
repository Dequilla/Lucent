/**
* \file Vertex.h
* \brief Contains vertex definitions
*/

#pragma once

#include <vector>

#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	/**
	* \brief A vertex structure
	*
	* Contains:
	*	- position
	*	- normal vector
	*	- texture coordinate
	*/
	struct Vertex
	{
		glm::vec3 position;		/**< A 3D position, x, y, z */
		glm::vec3 normal;		/**< A 3D vector describing this Vertex normal */
		glm::vec2 textureCoord; /**< A 2D vector for texture coordinates */
	};

	/**
	* \var VertexArray
	* \brief A std::vector with Vertex as it's template argument
	*/
	typedef std::vector<Vertex> VertexArray;

	/**
	* \var IndexArray
	* \brief A std::vector with unsigned int as it's template argument
	*/
	typedef std::vector<unsigned int> IndexArray;

}}