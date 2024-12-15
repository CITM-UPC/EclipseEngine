#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "AABB.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    std::string name;
    Transform transform;
    std::vector<std::unique_ptr<Component>> components; // Store components

    // Parent reference (nullable)
    std::shared_ptr<GameObject> parent;
	std::list<std::shared_ptr<GameObject>> children;

public:
    GameObject();
    ~GameObject();

    void Update();    // Update and draw the game object
    void Draw(Shader& shader, Camera& camera, const glm::mat4& parentTransform);

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);    // Add a component to the game object
    template<typename T>
    void RemoveComponent();             // Remove a component of a specific type
    template<typename T>
	T* GetComponent();                  // Get a component of a specific type
    void DeleteAllComponents();

	bool HasParent() const { return parent != nullptr; }
    inline void AddChild(std::shared_ptr<GameObject> child);    // Add a child game object
    void DeleteAllChildren();
    const std::list<std::shared_ptr<GameObject>>& GetChildren() const { return children; }    // Add a child game object
    glm::mat4 CalculateWorldTransform(const glm::mat4& parentTransform) const; // Helper to calculate world transform

    std::string GetName() const { return name; }
    AABB GetAABB(); // Returns the AABB in world space
    void UpdateAABB(const glm::mat4& parentTransform);
    void SetTexture(const std::string& texturePath);
    GLuint GetTextureID() const { return textureID; }

private:
    AABB localAABB;
    GLuint textureID;
    std::string currentTexturePath;
    void LoadTexture(const std::string& texturePath);
    void UpdateTexture(const std::string& texturePath);

};

// Template member function definitions should go here as well
template<typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->SetOwner(this);
    T* componentPtr = component.get();
    components.push_back(std::move(component));
    return componentPtr;
}

template<typename T>
void GameObject::RemoveComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    components.erase(std::remove_if(components.begin(), components.end(),
        [](const std::unique_ptr<Component>& component) {
            return dynamic_cast<T*>(component.get()) != nullptr;
        }), components.end());
}

template<typename T>
T* GameObject::GetComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    for (const auto& component : components) {
        if (T* castedComponent = dynamic_cast<T*>(component.get())) {
            return castedComponent;
        }
    }
    return nullptr; // If no matching component, return nullptr
}

inline void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    children.push_back(child);
    child->parent = shared_from_this(); // Set this object as the parent of the child
}

#endif // GAME_OBJECT_H
