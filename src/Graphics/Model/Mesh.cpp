#include "Graphics/Model/Mesh.h"

void lu::graphics::Mesh::setupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// Vertex textureCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

	glBindVertexArray(0);
}

lu::graphics::Mesh::Mesh(VertexArray vertices, IndexArray indices, Material material)
{
	m_vertices = vertices;
	m_indices = indices;
	this->material = material;

	setupMesh();
}

void lu::graphics::Mesh::draw()
{
	material.shader.use(); // use the material shader

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number = "";
		std::string name = "";

		if (material.textures[i].type == TEXTURE_DIFFUSE)
		{
			name = "texture_diffuse";
			number = std::to_string(diffuseNr);
			diffuseNr++;
		}
		else if (material.textures[i].type == TEXTURE_SPECULAR)
		{
			name = "texture_specular";
			number = std::to_string(specularNr);
			specularNr++;
		}

		std::string shaderUniform = ("material." + name + number).c_str();
		material.shader.setInt(shaderUniform, i);
		glBindTexture(GL_TEXTURE_2D, material.textures[i].id);
	}

	material.shader.setFloat("material.shininess", material.shininess);
	material.shader.setFloat("material.opacity", material.opacity);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}