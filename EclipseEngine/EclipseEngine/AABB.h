#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

class AABB {
public:
    glm::vec3 min;
    glm::vec3 max;

    AABB() : min(glm::vec3(FLT_MAX)), max(glm::vec3(-FLT_MAX)) {}

    void Expand(const glm::vec3& point);
    bool Intersects(const AABB& other) const;
    void Transform(const glm::mat4& transform);
};

#endif // AABB_H
