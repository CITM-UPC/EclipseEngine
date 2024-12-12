#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GameObject.h"
#include "VBO.h"
#include "Texture.h"

class ModelLoader 
{
public:
    // Static method to load a model from a file path
    std::shared_ptr<GameObject> LoadModel(const std::string& filepath);

    std::shared_ptr<GameObject> ProcessNode(aiNode* node, const aiScene* scene, std::shared_ptr<GameObject>& model);

    void ProcessMesh(aiMesh* mesh, const aiScene* scene,
        std::vector<Vertex>& vertices,
        std::vector<GLuint>& indices,
        std::vector<Texture>& textures);

private:
    static std::vector<Texture> LoadMaterialTextures(aiMaterial* material,
        aiTextureType type,
        const std::string& typeName);
};

#endif // MODELLOADER_H
