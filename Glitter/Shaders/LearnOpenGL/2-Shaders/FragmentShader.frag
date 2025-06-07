#version 410 core

out vec4 FragColor;
in vec4 vertexColor;
in vec4 vertexPosition;

uniform vec4 outColor;

void main() {
    FragColor = vertexPosition; // Set the fragment color to orange
}