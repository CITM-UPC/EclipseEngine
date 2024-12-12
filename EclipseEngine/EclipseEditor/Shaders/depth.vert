#version 330 core

layout (location = 0) in vec3 aPos; // Vertex position

uniform mat4 model;     // Model matrix
uniform mat4 camMatrix; // View-projection matrix (camera transformation)

out vec4 fragPos; // Fragment position in clip space

void main()
{
    // Calculate the clip-space position
    fragPos = camMatrix * model * vec4(aPos, 1.0);

    // Pass the position to the next stage
    gl_Position = fragPos;
}
