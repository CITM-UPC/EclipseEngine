#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "AABB.h"

class Mesh; // Forward declaration
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    std::string name;
    Transform transform;
    std::unique_ptr<Material> material; // Using unique_ptr for automatic memory management
    std::unique_ptr<Mesh> mesh;         // Using unique_ptr for automatic memory management

    // Parent reference (nullable)
    std::shared_ptr<GameObject> parent;
	std::list<std::shared_ptr<GameObject>> children;

public:
    GameObject();
    ~GameObject();

    void Update();    // Update and draw the game object
    void Draw(Shader& shader, Camera& camera, const glm::mat4& parentTransform);
    AABB GetAABB() const; // Returns the AABB in world space

    template<typename T, typename... Args>
    void AddComponent(Args&&... args);    // Add a component to the game object
    inline void AddChild(std::shared_ptr<GameObject> child);    // Add a child game object

    template<typename T>
    T* GetComponent();    // Retrieve a component of a specific type
    std::string GetName() const { return name; }
    const std::list<std::shared_ptr<GameObject>>& GetChildren() const { return children; }    // Add a child game object

	bool HasParent() const { return parent != nullptr; }
    void UpdateChildrenTransforms();
    glm::mat4 CalculateWorldTransform(const glm::mat4& parentTransform) const; // Helper to calculate world transform


    void SetTexture(const std::string& texturePath);
    GLuint GetTextureID() const;

private:
    GLuint textureID;
    std::string currentTexturePath;
    void LoadTexture(const std::string& texturePath);
    void UpdateTexture(const std::string& texturePath);

};

// Template member function definitions should go here as well
template<typename T, typename... Args>
void GameObject::AddComponent(Args&&... args) {
    if constexpr (std::is_same<T, Mesh>::value) {
        mesh = std::make_unique<Mesh>(std::forward<Args>(args)...);
    }
    else if constexpr (std::is_same<T, Material>::value) {
        material = std::make_unique<Material>(std::forward<Args>(args)...);
    }
    // Add more components as needed
}

template<typename T>
T* GameObject::GetComponent() {
    if constexpr (std::is_same<T, Transform>::value) {
        return &transform; // Return the address of the Transform
    }
    else if constexpr (std::is_same<T, Material>::value) {
        return material.get(); // Return the raw pointer of the unique_ptr
    }
    else if constexpr (std::is_same<T, Mesh>::value) {
        return mesh.get(); // Return the raw pointer of the unique_ptr
    }
    return nullptr; // If no matching component, return nullptr
}

inline void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    children.push_back(child);
    child->parent = shared_from_this(); // Set this object as the parent of the child
}

#endif // GAME_OBJECT_H
