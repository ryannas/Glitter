#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 outTexCoord;

void main() {
    gl_Position = vec4(position, 1.0);
    outColor = vec4(color, 1.0); // Pass the color to the fragment shader
    outTexCoord = texCoord; // Pass the texture coordinates to the fragment shader
}