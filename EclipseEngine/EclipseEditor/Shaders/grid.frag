#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 vertexColor;

uniform vec3 gridColor; // uniform for grid color

void main()
{
    FragColor = vec4(vertexColor, 1.0f);
}