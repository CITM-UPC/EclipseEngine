#ifndef RESOURCE_IMPORTER_H
#define RESOURCE_IMPORTER_H\

#include <filesystem>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IL/il.h>

#include "EclipseEngine/VBO.h"

namespace fs = std::filesystem;

class ResourceImporter
{
	std::unordered_map<std::string, std::string> fileHashes;

public:
	void ScanAssetFolder(const std::string& folderPath);
	void ImportAsset(const std::string& filePath);
	void ImportAllAssets();

	void ConvertFBX(const std::string& filePath);
	void ConvertTexture(const std::string& filePath);

	void ProcessNode(aiNode* node, const aiScene* scene, const std::string& basePath, std::vector<std::string>& meshFiles);
	void ProcessMesh(aiMesh* mesh, const std::string& filePath);
};

#endif // RESOURCE_IMPORTER_H