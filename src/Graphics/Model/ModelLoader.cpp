#include "Graphics/Model/ModelLoader.h"

std::unordered_map<std::string, lu::graphics::Model>
  lu::graphics::ModelLoader::m_models;

lu::graphics::Mesh
lu::graphics::ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene)
{
    VertexArray vertices;
    IndexArray indices;
    Material material;

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
            vertex.textureCoord = vec;
        }
        else
            vertex.textureCoord = glm::vec2(0.0f, 0.0f);

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

    if (mesh->mMaterialIndex >= 0)
    {
        // How to get material properties
        // https://sourceforge.net/p/assimp/discussion/817654/thread/a3576c21/

        aiMaterial *assimpMaterial = scene->mMaterials[mesh->mMaterialIndex];

        float opacity;
        if (aiReturn_SUCCESS == assimpMaterial->Get(AI_MATKEY_OPACITY, opacity))
        {
            // How hard we should treat any translucent texels etc
            material.opacity = opacity;
        }

        // Choose shader based on if we need blending or not
        if (opacity >= 1.0f)
        {
            lu::graphics::ShaderProperties properties;
            lu::graphics::ShaderLoader loader;
            properties.vPath = "Shaders/Dynamic/opaque_sd_vertex.glsl";
            properties.fPath = "Shaders/Dynamic/opaque_sd_fragment.glsl";
            material.shader = loader.loadShader(properties, true);
        }
        else if (opacity < 1.0f) // Use blending shader to get opacity
        {
            material.m_materialProperties =
              material.m_materialProperties | MAT_BLEND;

            lu::graphics::ShaderProperties properties;
            lu::graphics::ShaderLoader loader;
            properties.vPath = "Shaders/Dynamic/transparent_sd_vertex.glsl";
            properties.fPath = "Shaders/Dynamic/transparent_sd_fragment.glsl";
            material.shader = loader.loadShader(properties, true);
        }

        float shininess;
        if (aiReturn_SUCCESS ==
            assimpMaterial->Get(AI_MATKEY_SHININESS, shininess))
        {
            material.shininess = shininess;
        }

        std::vector<Texture> diffuseMaps = loadMaterialTextures(
          assimpMaterial, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
        material.textures.insert(
          material.textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(
          assimpMaterial, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
        material.textures.insert(
          material.textures.end(), specularMaps.begin(), specularMaps.end());
    }

    Mesh result(vertices, indices, material);
    result.m_name = mesh->mName.C_Str();

    return result;
}

void
lu::graphics::ModelLoader::processNode(aiNode *node, const aiScene *scene)
{
    // Process meshes of this node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_currProcessedModel.m_meshes.push_back(
          std::make_shared<Mesh>(processMesh(mesh, scene)));
    }

    // Now process its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::vector<lu::graphics::Texture>
lu::graphics::ModelLoader::loadMaterialTextures(aiMaterial *mat,
                                                aiTextureType type,
                                                TextureType ceTexType)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString texFileName;
        mat->GetTexture(type, i, &texFileName);

        // TODO: Check if already loaded (avoid duplicates)
        Texture texture;
        texture.id = loadTexture(
          (m_currProcessedModel.m_directory + "/" + texFileName.C_Str())
            .c_str());
        texture.type = ceTexType;

        textures.push_back(texture);
    }

    return textures;
}

lu::graphics::Model
lu::graphics::ModelLoader::loadModel(std::string path)
{
    if (!(m_models.count(path) > 0))
    {
        // If model doesn't already exist load it
        Assimp::Importer importer;

        // Triangulate since we currently only support triangles, flipUV's
        // because OpenGL, generate normals if they dont exist
        const aiScene *scene = importer.ReadFile(
          path,
          aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
            !scene->mRootNode)
        {
            lu::core::log("Failed importing model(path: " + path +
                            "), error: " + importer.GetErrorString(),
                          lu::core::LOG_WARNING);
            return Model();
        }

        // Clear any previous data from m_currProcessedModel
        m_currProcessedModel.m_meshes.clear();

        // Get directory
        m_currProcessedModel.m_directory =
          path.substr(0, path.find_last_of('/'));

        // Fills up m_currProcessedModel
        processNode(scene->mRootNode, scene);

        // Emplace
        m_models.emplace(path, m_currProcessedModel);
    }

    return m_models.at(path);
}
