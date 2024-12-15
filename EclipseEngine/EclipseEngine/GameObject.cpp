#define STB_IMAGE_IMPLEMENTATION

#include "GameObject.h"
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
    // Update the current GameObject
    for (auto& component : components) {
        component->Update();
    }
}

// Compute world transform
glm::mat4 GameObject::CalculateWorldTransform(const glm::mat4& parentTransform) const 
{
	if (parent){
		return parent->CalculateWorldTransform(parentTransform) * transform.GetMatrix(); // Combine parent's and local transform
	} else {
        return transform.GetMatrix();
    }
}

void GameObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentTransform)
{
    // Get the model matrix from the Transform component
    glm::mat4 objectModel = CalculateWorldTransform(parentTransform); // Get the transformation matrix from Transform

    // Activate the shader program
    shader.Activate();
	shader.SetMat4("model", objectModel);
    shader.SetFloat("outlining", 1.05f);
    
	if (Material* material = GetComponent<Material>()) material->BindTextures(shader);
    if (Mesh* mesh = GetComponent<Mesh>()) mesh->Draw(shader, camera);

    for (const auto& child : children) {
        child->Draw(shader, camera, objectModel);
    }
}

void GameObject::SetTexture(const std::string& texturePath)
{
    if (currentTexturePath != texturePath) {
        currentTexturePath = texturePath;
        UpdateTexture(texturePath);
    }
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

AABB GameObject::GetAABB(){
    AABB worldAABB;
    if (Mesh* mesh = GetComponent<Mesh>()) {
        worldAABB = mesh->GetWorldAABB(transform.GetMatrix());
    }
    for (const auto& child : children) {
        worldAABB.Expand(child->GetAABB().min);
        worldAABB.Expand(child->GetAABB().max);
    }
    return worldAABB;
}

void GameObject::UpdateAABB(const glm::mat4& parentTransform)
{
    if (auto mesh = GetComponent<Mesh>()) {
        localAABB = mesh->GetWorldAABB(parentTransform);
    }

    for (const auto& child : children) {
        child->UpdateAABB(CalculateWorldTransform(parentTransform));
    }
}

void GameObject::DeleteAllComponents() {
    components.clear();
}

void GameObject::DeleteAllChildren() {
    for (auto& child : children) {
        child->DeleteAllComponents();
        child->DeleteAllChildren();
    }
    children.clear();
}