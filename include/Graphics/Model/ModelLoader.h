/**
 * \file ModelLoader.h
 */
#pragma once

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "Graphics/Model/Material.h"
#include "Graphics/Model/Mesh.h"
#include "Graphics/Model/Model.h"

#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderLoader.h"

#include "Core/Utility/log.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace lu
{
    namespace graphics
    {

        /**
         * \brief Loads models
         *
         * Loads and contains the original models
         * Keeps track of duplicates
         */
        class ModelLoader
        {
            private:
                // string - path (avoids loading duplicates)
                static std::unordered_map<std::string, Model> m_models;

                // Loading functions (Assimp)
                Model m_currProcessedModel;
                Mesh processMesh(aiMesh *mesh, const aiScene *scene);
                void processNode(aiNode *node, const aiScene *scene);

                std::vector<Texture> loadMaterialTextures(
                  aiMaterial *mat,
                  aiTextureType type,
                  TextureType ceTexType);

            public:
                ModelLoader() {}

                /**
                 * \brief Load a model
                 *
                 * @param path Path to model file (eg: a .obj file)
                 */
                Model loadModel(std::string path);
        };

    }
}