#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

class Transform : public Component
{
public:
    Transform();

    glm::mat4 GetMatrix() const;
    glm::mat4 GetWorldMatrix(const glm::mat4& parentMatrix) const;
    void SetMatrix(const glm::mat4& matrix);

    void SetPosition(const glm::vec3& newPosition);
    void SetRotation(const glm::quat& newRotation);
    void SetRotationFromEuler(const glm::vec3& eulerAngles); // Optional
    void SetScale(const glm::vec3& newScale);
    void SetFromMatrix(const glm::mat4& matrix);

    glm::vec3 GetEulerAngles() const;

    void Update() override;

public:
    glm::vec3 position;
    glm::quat rotation; // Quaternion for robust 3D rotations
    glm::vec3 scale;
};

#endif // TRANSFORM_H
