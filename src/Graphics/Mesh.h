#pragma once

#include <vector>

#include "GLM/glm.hpp"

#include "Graphics/Shader.h"

namespace ce { namespace graphics {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct Texture
	{
		// OpenGL id
		unsigned int id;
			
		// Type EG: texture_diffuse
		std::string type;

		// Path to avoid loading textures twice
		std::string path;
	};

	struct Material
	{
		std::vector<Texture> textures;
		float shininess = 32.0f;
	};

	class Mesh
	{
	private:
		// OpenGL buffers and objects
		unsigned int VAO, VBO, EBO;

		// Sets all the buffers and objects
		// Also sends data to the graphics card
		void setupMesh();

	protected:
		// Mesh data
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;

		std::vector<Material> m_materials;

	public:

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Material> materials);

		void draw(Shader shader);

	};

} }