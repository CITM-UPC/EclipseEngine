
#define GLM_ENABLE_EXPERIMENTAL

#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>

struct quaternion {
    double w, x, y, z;
};

quaternion quat(double roll, double pitch, double yaw) {
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;

}

Transform::Transform() : position(0.0f), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f) {}

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::mat4_cast(rotation); // Convert quaternion to matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Transform::GetWorldMatrix(const glm::mat4& parentMatrix) const
{
    return parentMatrix * GetMatrix();
}

void Transform::SetMatrix(const glm::mat4& matrix)
{
    glm::vec3 skew;
    glm::vec4 perspective;

    // Decompose the matrix
    bool success = glm::decompose(matrix, scale, rotation, position, skew, perspective);
    if (success)
    {
        // Normalize the quaternion to avoid skew
        rotation = glm::normalize(rotation);
    }
    else
    {
        // Handle failure (e.g., reset to defaults)
        position = glm::vec3(0.0f);
        rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f);
    }
}

void Transform::SetPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}

void Transform::SetRotation(const glm::quat& newRotation)
{
    rotation = glm::normalize(newRotation);
}

void Transform::SetRotationFromEuler(const glm::vec3& eulerAngles)
{
    rotation = glm::normalize(glm::quat(glm::radians(eulerAngles)));
}

void Transform::SetScale(const glm::vec3& newScale)
{
    scale = glm::max(newScale, glm::vec3(0.0001f)); // Prevent zero or negative scales
}

void Transform::SetFromMatrix(const glm::mat4& matrix) {
    position = glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
    rotation = glm::quat_cast(matrix);
    scale = glm::vec3(glm::length(glm::vec3(matrix[0])),
        glm::length(glm::vec3(matrix[1])),
        glm::length(glm::vec3(matrix[2])));
}

glm::vec3 Transform::GetEulerAngles() const
{
    return glm::degrees(glm::eulerAngles(rotation));
}

void Transform::Update()
{
}
