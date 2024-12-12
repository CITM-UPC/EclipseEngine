#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;

void main()
{
    //FragColor = vec4(color, 1.0f);
    //FragColor = vec4(1.0f) - vec4(color, 1.0f); //inverted color

   // vec3 _normal = normalize(normal);
    FragColor =  texture(diffuse0, texCoord);
}