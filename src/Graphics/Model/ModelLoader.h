#pragma once

#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include "Graphics/Model/Mesh.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Model/Material.h"

#include "Graphics/Shader/ShaderLoader.h"
#include "Graphics/Shader/Shader.h"

#include "Core/Utility/log.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace ce { namespace graphics { 

	//             
	// ModelLoader 
	//  - Loads and contains the original models
	//  - Prevents loading same models twice, less memory used
	class ModelLoader
	{
	private:
		// string - path (avoids loading duplicates) 
		std::unordered_map<std::string, Model> m_models;

		// Loading functions (Assimp)
		Model m_currProcessedModel;
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void processNode(aiNode* node, const aiScene* scene);
		
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType ceTexType);

	public:
		ModelLoader() {}

		Model loadModel(std::string path);
	};

}}