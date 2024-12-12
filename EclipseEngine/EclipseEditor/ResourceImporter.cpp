#include "ResourceImporter.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>

std::string ComputeFileHash(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) return "";

	// Initialize the OpenSSL context for SHA256
	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	const EVP_MD* sha256 = EVP_sha256();
	EVP_DigestInit_ex(mdctx, sha256, nullptr);

	char buffer[8192];
	while (file.read(buffer, sizeof(buffer))) {
		EVP_DigestUpdate(mdctx, buffer, file.gcount());
	}
	EVP_DigestUpdate(mdctx, buffer, file.gcount());

	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len = 0;
	EVP_DigestFinal_ex(mdctx, hash, &hash_len);
	EVP_MD_CTX_free(mdctx); // Free the context

	// Convert the hash to a hex string
	std::ostringstream hashStream;
	for (unsigned int i = 0; i < hash_len; ++i) {
		hashStream << std::hex << static_cast<int>(hash[i]);
	}

	return hashStream.str();
}

void ResourceImporter::ScanAssetFolder(const std::string& assetFolder)
{
	for (const auto& entry : fs::recursive_directory_iterator(assetFolder)) {
		if (entry.is_regular_file()) {
			std::string filePath = entry.path().string();
			std::string fileHash = ComputeFileHash(filePath);

			// Check for new or modified files by comparing the hash
			if (fileHashes.find(filePath) == fileHashes.end() || fileHashes[filePath] != fileHash) {
				fileHashes[filePath] = fileHash;
				ImportAsset(filePath); // Import the asset
			}
		}
	}
}

void ResourceImporter::ImportAsset(const std::string& filePath)
{
	// Import the asset
	std::cout << "Importing asset: " << filePath << std::endl;

	std::string basePath = fs::path(filePath).replace_extension("").string();

	std::string fbxPath = basePath + ".fbx";
	std::string emodelPath = "Resources/Library/emodel/" + fs::path(filePath).stem().string() + ".emodel";

	bool fbxExists = fs::exists(fbxPath);
	bool emodelExists = fs::exists(emodelPath);

	const std::string extension = fs::path(filePath).extension().string();
	if (fbxExists && !emodelExists)
	{
		if (extension == ".fbx") {
			ConvertFBX(filePath);
		}
		else if (extension == ".png" || extension == ".jpg") {
			ConvertTexture(filePath);
		}
	}
	
}

void ResourceImporter::ImportAllAssets()
{
	// Import all assets in the asset folder
	ScanAssetFolder("Assets");
}

void ResourceImporter::ConvertFBX(const std::string& filePath)
{
	// Convert FBX file to engine format
	std::cout << "Converting FBX file..." << std::endl;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// Save as custom .model file
	std::string modelFilePath = "Resources/Library/emodel/" + fs::path(filePath).stem().string() + ".emodel";
	fs::create_directories("Resources/Library/emodel");

	// Open .model file for writing
	std::ofstream outFile(modelFilePath, std::ios::binary);
	if (!outFile.is_open()) {
		std::cerr << "Failed to create .model file: " << modelFilePath << std::endl;
		return;
	}

	std::vector<std::string> meshFiles;
	ProcessNode(scene->mRootNode, scene, filePath, meshFiles);

	outFile << "{\n";
	outFile << "  \"meshes\": [\n";
	for (size_t i = 0; i < meshFiles.size(); ++i) {
		outFile << "    \"" << meshFiles[i] << "\"";
		if (i < meshFiles.size() - 1) outFile << ",";
		outFile << "\n";
	}
	outFile << "  ]\n";
	outFile << "}\n";

	outFile.close();
	std::cout << "FBX converted and saved as: " << modelFilePath << std::endl;
}

void ResourceImporter::ProcessNode(aiNode* node, const aiScene* scene, const std::string& basePath, std::vector<std::string>& meshFiles)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		std::string meshFilePath = "Resources/Library/emesh/" + fs::path(basePath).stem().string() + "_mesh_" + node->mName.C_Str() + std::to_string(i) + ".emesh";
		fs::create_directories("Resources/Library/emesh");
		ProcessMesh(mesh, meshFilePath);
		meshFiles.push_back(meshFilePath);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene, basePath, meshFiles);
	}
}

void ResourceImporter::ProcessMesh(aiMesh* mesh, const std::string& filePath)
{
	std::ofstream outFile(filePath, std::ios::binary);
	if (!outFile.is_open()) {
		std::cerr << "Failed to create .mesh file: " << filePath << std::endl;
		return;
	}

	// Save vertex data
	outFile << "vertices " << mesh->mNumVertices << "\n";
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		outFile << mesh->mVertices[i].x << " "
			<< mesh->mVertices[i].y << " "
			<< mesh->mVertices[i].z << "\n";
	}

	// Save indices
	outFile << "indices " << mesh->mNumFaces * 3 << "\n";
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			outFile << face.mIndices[j] << " ";
		}
		outFile << "\n";
	}

	outFile.close();
	std::cout << "Mesh saved as: " << filePath << std::endl;
}

void ResourceImporter::ConvertTexture(const std::string& filePath)
{
	std::cout << "Converting texture file: " << filePath << std::endl;

	//ilInit();
	//ILuint imageID;
	//ilGenImages(1, &imageID);
	//ilBindImage(imageID);

	//if (!ilLoadImage(filePath.c_str())) {
	//	std::cerr << "Failed to load texture: " << filePath << std::endl;
	//	ilDeleteImages(1, &imageID);
	//	return;
	//}

	//// Save as custom .tex file
	//std::string texFilePath = fs::path(filePath).replace_extension(".tex").string();
	//if (!ilSaveImage(texFilePath.c_str())) {
	//	std::cerr << "Failed to save texture as .tex: " << texFilePath << std::endl;
	//}
	//else {
	//	std::cout << "Texture saved as: " << texFilePath << std::endl;
	//}

	//ilDeleteImages(1, &imageID);
}