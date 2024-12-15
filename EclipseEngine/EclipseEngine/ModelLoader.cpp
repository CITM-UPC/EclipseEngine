#include "ModelLoader.h"
#include <iostream>
#include <set>
#include "Logger.h"

glm::mat4 aiMat4ToMat4(const aiMatrix4x4& from) {
    glm::mat4 mat;
    for (int c = 0; c < 4; ++c) for (int r = 0; r < 4; ++r) mat[c][r] = from[r][c];
    return mat;
}

std::shared_ptr<GameObject> ModelLoader::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return std::shared_ptr<GameObject>(); // Return an empty GameObject
    }

    auto model = std::make_shared<GameObject>();
    model->name = scene->mRootNode->mName.C_Str(); // Name the model based on the root node

    // Skip the root node itself and process its children as the top-level nodes
    for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i) {
        ProcessNode(scene->mRootNode->mChildren[i], scene, model);
    }

    return model;
}

std::shared_ptr<GameObject> ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, std::shared_ptr<GameObject>& parent) {
    
    std::string nodeName = node->mName.C_Str();

    if (nodeName.find("$AssimpFbx$") != std::string::npos) {
        // Recursively process children without creating a GameObject for this node
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, parent);
        }
        return nullptr; // Skip this node
    }

    // Create a new GameObject for the current node
    std::shared_ptr<GameObject> currentNode = std::make_shared<GameObject>();
    currentNode->name = nodeName;

    // Set the transformation for the current node
    currentNode->transform.SetFromMatrix(aiMat4ToMat4(node->mTransformation));

    // Process all meshes for this node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        ProcessMesh(mesh, scene, vertices, indices, textures);
        std::cout << "Mesh has " << vertices.size() << " vertices and " << indices.size() << " indices.\n";
        // Add a Mesh component to the current node
        currentNode->AddComponent<Mesh>(vertices, indices, textures);
    }

    // Add the current node as a child of the parent GameObject
    parent->AddChild(currentNode);

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene, currentNode);
    }

	return currentNode;
}

void ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene,
    std::vector<Vertex>& vertices,
    std::vector<GLuint>& indices,
    std::vector<Texture>& textures)
{
    // Process vertex positions, normals, and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Positions
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.position = position;

        // Normals
        if (mesh->HasNormals())
        {
            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            vertex.normal = normal;
        }

		if (mesh->HasVertexColors(0))
        {
            glm::u8vec3 color;
		    color.x = mesh->mColors[0][i].r * 255;
		    color.y = mesh->mColors[0][i].g * 255;
		    color.z = mesh->mColors[0][i].b * 255;
		    vertex.color = color;
        }

        // Texture Coordinates
        if (mesh->HasTextureCoords(0)) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texUV = vec;
        }
        else {
            vertex.texUV = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

     //Process textures
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        textures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
    }
}

std::vector<Texture> ModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
    std::vector<Texture> textures;
    std::set<std::string> loadedTextures; // To track loaded texture paths

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str; // For texture file path
        mat->GetTexture(type, i, &str);

        // Check if texture is already loaded
        if (loadedTextures.find(str.C_Str()) != loadedTextures.end())
        {
            continue; // Skip if already loaded
        }

        // Load the texture and add it to the vector
        Texture texture(str.C_Str(), typeName, textures.size(), GL_RGBA, GL_UNSIGNED_BYTE);
        textures.push_back(texture);
        loadedTextures.insert(str.C_Str()); // Track the loaded texture path
    }
    return textures;
}

