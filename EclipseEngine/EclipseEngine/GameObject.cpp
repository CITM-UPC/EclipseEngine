#include "GameObject.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

GameObject::GameObject()
{
    // Initialization code for the GameObject
}

GameObject::~GameObject()
{
    // placeholder for Cleanup
}

void GameObject::Update()
{
    // placeholder for Update
}

// Compute world transform
glm::mat4 GameObject::CalculateWorldTransform(const glm::mat4& parentTransform) const {

	if (parent)
	{
		return parentTransform * transform.GetMatrix(); // Combine parent's and local transform
	}
    else {

    return transform.GetMatrix();
    }
}

void GameObject::UpdateChildrenTransforms()
{
	for (const auto& child : children) {
		child->transform.SetMatrix(CalculateWorldTransform(child->parent->transform.GetMatrix()));
		child->UpdateChildrenTransforms();
	}
}

void GameObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentTransform)
{
    // Get the model matrix from the Transform component
    glm::mat4 objectModel = CalculateWorldTransform(parentTransform); // Get the transformation matrix from Transform

    // Activate the shader program
    if(!material)
    { 
        std::vector<Texture> defaultTex{ Texture("Resources/Assets/Textures/default.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE) };
        this->AddComponent<Material>(defaultTex); // Add a default material if none exists
    }

    shader.Activate();
	shader.SetMat4("model", objectModel);
    shader.SetFloat("outlining", 1.05f);

    if(material) material.get()->BindTextures(shader); // If it has material, bind it
    if (mesh) mesh->Draw(shader, camera);   // Code to draw the game object (calls Draw on the mesh if it exists)

    for (const auto& child : children) {
		glm::mat4 childModel = CalculateWorldTransform(parentTransform);
        child->Draw(shader, camera, childModel);
    }
}

void GameObject::SetTexture(const std::string& texturePath)
{
    if (currentTexturePath != texturePath) {
        currentTexturePath = texturePath;
        UpdateTexture(texturePath);
    }
}

GLuint GameObject::GetTextureID() const
{
	return textureID;
}

void GameObject::LoadTexture(const std::string& texturePath)
{
    int width, height, channels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
}

void GameObject::UpdateTexture(const std::string& texturePath)
{
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
    LoadTexture(texturePath);
}

AABB GameObject::GetAABB() const {
    AABB worldAABB;
    if (mesh) {
        worldAABB = mesh->GetWorldAABB(transform.GetMatrix());
    }
    for (const auto& child : children) {
        worldAABB.Expand(child->GetAABB().min);
        worldAABB.Expand(child->GetAABB().max);
    }
    return worldAABB;
}