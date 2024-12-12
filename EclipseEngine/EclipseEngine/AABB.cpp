#include "AABB.h"
#include <algorithm>

void AABB::Expand(const glm::vec3& point) {
    min = glm::min(min, point);
    max = glm::max(max, point);
}

bool AABB::Intersects(const AABB& other) const {
    return (min.x <= other.max.x && max.x >= other.min.x) &&
        (min.y <= other.max.y && max.y >= other.min.y) &&
        (min.z <= other.max.z && max.z >= other.min.z);
}

void AABB::Transform(const glm::mat4& transform) {
    glm::vec3 corners[8] = {
        glm::vec3(min.x, min.y, min.z),
        glm::vec3(max.x, min.y, min.z),
        glm::vec3(min.x, max.y, min.z),
        glm::vec3(max.x, max.y, min.z),
        glm::vec3(min.x, min.y, max.z),
        glm::vec3(max.x, min.y, max.z),
        glm::vec3(min.x, max.y, max.z),
        glm::vec3(max.x, max.y, max.z),
    };

    AABB transformedAABB;
    for (const auto& corner : corners) {
        glm::vec4 transformedCorner = transform * glm::vec4(corner, 1.0f);
        transformedAABB.Expand(glm::vec3(transformedCorner));
    }

    *this = transformedAABB;
}
