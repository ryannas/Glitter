#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform float offset; // Uniform variable for offset

out vec4 vertexColor;
out vec4 vertexPosition;

void main() {
    vec3 adjustedPosition = vec3(position.x + offset, -position.y + offset, 0); // Apply the offset to the vertex position
    gl_Position = vec4(adjustedPosition, 1.0);

    vertexColor = vec4(color, 1.0); // Set the vertex color to orange
    vertexPosition = gl_Position; // Pass the position to the fragment shader
}