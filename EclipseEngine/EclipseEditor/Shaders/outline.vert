#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;
uniform float outlining;

void main()
{
    vec3 scaledPos = aPos * outlining;
    gl_Position = camMatrix * model * vec4(scaledPos, 1.0);
}