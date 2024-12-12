#version 330 core

out vec4 FragColor;

in vec3 fragPos;   // Interpolated world-space position
in vec3 normal;    // Interpolated world-space normal
in vec3 color;     // Interpolated color
in vec2 texCoord;  // Interpolated texture coordinates

uniform sampler2D diffuse0; // Diffuse texture

void main()
{
    // Use the fragment's world-space position (fragPos)
    vec3 worldPos = fragPos;

    // Example: Encode world position in color for debugging
    vec3 posColor = (worldPos + vec3(1.0)) * 0.5; // Map world pos (-1 to 1) to color range (0 to 1)

    // Final fragment color combining texture and encoded position
    vec4 texColor = texture(diffuse0, texCoord);
    FragColor = vec4(posColor, 1.0);
}
