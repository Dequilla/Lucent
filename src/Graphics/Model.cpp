#include "Model.h"

void ce::graphics::Model::loadModel(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "CE: Failed importing model, error: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void ce::graphics::Model::processNode(aiNode * node, const aiScene * scene)
{
	// Process this nodes meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	// Now do the same process for this nodes children (wooo, recursion!)
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

ce::graphics::Mesh ce::graphics::Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Vertecies
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		// If it has coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int x = 0; x < face.mNumIndices; x++)
		{
			indices.push_back(face.mIndices[x]);
		}
	}

	// Material / textures
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return ce::graphics::Mesh(vertices, indices, textures);
}

std::vector<ce::graphics::Texture> ce::graphics::Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString texFileName;
		mat->GetTexture(type, i, &texFileName);

		// Check if texture is already loaded, if so add the already loaded one
		bool alreadyLoaded = false;
		for (unsigned int x = 0; x < m_loadedTextures.size(); x++)
		{
			if (std::strcmp(m_loadedTextures[x].path.c_str(), texFileName.C_Str()) == 0)
			{
				textures.push_back(m_loadedTextures[x]);
				alreadyLoaded = true;
				break;
			}
		}

		if (!alreadyLoaded)
		{
			Texture texture;
			texture.id = loadTexture((this->m_directory + "/" + texFileName.C_Str()).c_str()); // Apparently assimp only gets us the name, not the whole path
			texture.type = typeName;
			texture.path = texFileName.C_Str();

			textures.push_back(texture);
			m_loadedTextures.push_back(texture);
		}
	}

	return textures;
}

ce::graphics::Model::Model(std::string path)
{
	loadModel(path);
}

void ce::graphics::Model::rotate(float angle, glm::vec3 axis)
{
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), axis);
}

void ce::graphics::Model::translate(glm::vec3 axis)
{
	m_modelMatrix = glm::translate(m_modelMatrix, axis);
}

void ce::graphics::Model::scale(glm::vec3 scale)
{
	m_modelMatrix = glm::scale(m_modelMatrix, scale);
}

void ce::graphics::Model::draw(Shader shader)
{
	shader.setMat4("model", m_modelMatrix);

	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].draw(shader);
}