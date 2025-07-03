/**
 * \file Mesh.h
 */
#pragma once

#include "Graphics/Shader/Shader.h"

#include "Graphics/Model/Material.h"
#include "Graphics/Vertex.h"

namespace lu
{
    namespace graphics
    {

        /**
         * \brief A object representation of a mesh
         */
        class Mesh
        {
            protected:
                unsigned int m_VAO, m_VBO, m_EBO;

                VertexArray m_vertices;
                IndexArray m_indices;

                friend class ModelLoader;

                std::string m_name;

            private:
                // Set up buffers
                void setupMesh();

            public:
                /**
                 * \brief Construct mesh from a set of vertices, indices and a
                 * material
                 */
                Mesh(VertexArray vertices,
                     IndexArray indices,
                     Material material);

                /**
                 * \brief The material used by this mesh
                 */
                Material material;

                /**
                 * \brief Draw mesh
                 *
                 * To be updated currently very slow
                 */
                void draw();
        };

    }
}