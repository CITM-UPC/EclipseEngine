#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    virtual void Update() = 0; // To be overridden in each derived component

    void SetOwner(GameObject* owner) { this->owner = owner; }
    GameObject* GetOwner() const { return owner; }

private:
    GameObject* owner = nullptr; // Reference to the owning GameObject
};

#endif // COMPONENT_H