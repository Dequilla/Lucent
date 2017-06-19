#pragma once

#include <string>
#include <vector>

#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

namespace ce { namespace graphics { 

	class Model
	{
	private:
		std::vector<Texture> m_loadedTextures;
		std::vector<Mesh> m_meshes;
		std::string m_directory;

		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	protected:
	public:
		Model(std::string path);

		// TODO: possible idea, give models their shader when we create them? (the program that is)
		void draw(Shader shader);
	};

}}