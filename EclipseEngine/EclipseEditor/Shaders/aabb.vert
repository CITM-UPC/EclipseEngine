#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix; // Camera (view + projection) matrix
uniform mat4 model;      // World transform (model matrix)

void main() {
    // Apply the model (world transform) and camera (view + projection) transformations
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}