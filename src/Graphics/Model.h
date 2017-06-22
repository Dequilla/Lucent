#pragma once

#include <string>
#include <vector>

#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include "Graphics/ForwardRenderer.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace graphics { 

	class Model
	{
	private:
		std::vector<Texture> m_loadedTextures;
		std::vector<Mesh> m_meshes;
		std::string m_directory;

		glm::mat4 m_modelMatrix;

		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	protected:
	public:
		Model(std::string path);

		// TODO: These have to happen in a surten order?
		void rotate(float angle, glm::vec3 axis);
		void translate(glm::vec3 axis);
		void scale(glm::vec3 scale);

		// TODO: possible idea, give models(meshes) their shader when we create them? (the program that is)
		void draw(Shader shader);
		void draw(ForwardRenderer* renderer);
	};

}}