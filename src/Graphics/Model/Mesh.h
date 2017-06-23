#pragma once

#include "Graphics/Shader/Shader.h"

#include "Graphics/Vertex.h"
#include "Graphics/Model/Material.h"

namespace ce { namespace graphics {

	class Mesh
	{
	protected:
		unsigned int m_VAO, m_VBO, m_EBO;

		VertexArray m_vertices;
		IndexArray m_indices;

		// TODO: Lets not have duplicate materials
		Material m_material; // We have materials on a mesh-to-mesh basis
		
		friend class ModelLoader;

		std::string m_name;

	private:
		// Set up buffers
		void setupMesh();

	public:
		Mesh(VertexArray vertices, IndexArray indices, Material material);

		// TODO: TEMP FOR TEST
		void draw();
	};

}}