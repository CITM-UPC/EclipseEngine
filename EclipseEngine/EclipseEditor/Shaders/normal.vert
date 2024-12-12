#version 330 core

layout (location = 0) in vec3 aPos;   // Vertex position
layout (location = 1) in vec3 aNormal; // Vertex normal

out vec3 fragNormal;  // Pass the transformed normal to the fragment shader

uniform mat4 model;     // Model matrix
uniform mat4 camMatrix; // Combined view and projection matrix

void main()
{
    // Transform the normal to world space
    fragNormal = mat3(transpose(inverse(model))) * aNormal;

    // Calculate the final position of the vertex
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}
