#version 330 core

out vec4 FragColor;

in vec3 fragNormal; // Interpolated world-space normal

void main()
{
    // Normalize the normal
    vec3 normal = normalize(fragNormal);

    // Map normal components from [-1, 1] to [0, 1] for color visualization
    vec3 normalColor = (normal + vec3(1.0)) * 0.5;

    // Output the normal color
    FragColor = vec4(normalColor, 1.0);
}
