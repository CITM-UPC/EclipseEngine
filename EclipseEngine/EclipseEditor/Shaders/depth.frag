#version 330 core

in vec4 fragPos; // Fragment position in clip space

out vec4 FragColor;

uniform float near; // Near plane of the camera
uniform float far;  // Far plane of the camera

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Convert NDC to clip space depth
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    // Perspective division to get depth in NDC
    float depth = fragPos.z / fragPos.w;

    // Linearize depth for better visualization
    float linearDepth = LinearizeDepth(depth) / far;

    // Map depth to grayscale
    FragColor = vec4(vec3(linearDepth), 1.0);
}
