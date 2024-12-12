#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 fragPos;  // Position of the vertex in world space
out vec3 normal;   // Vertex normal
out vec3 color;    // Vertex color
out vec2 texCoord; // Texture coordinates

uniform mat4 camMatrix; // Combined view and projection matrix
uniform mat4 model;     // Model matrix (local to world space)

void main()
{
    // Calculate world-space position of the vertex
    fragPos = vec3(model * vec4(aPos, 1.0));

    // Pass other attributes to the fragment shader
    normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    color = aColor;
    texCoord = aTex;

    // Calculate final clip-space position
    gl_Position = camMatrix * vec4(fragPos, 1.0);
}