#version 410 core

out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    // FragColor = texture(texture1, outTexCoord);
    FragColor = mix(texture(texture0, outTexCoord), texture(texture1, vec2(-outTexCoord.x, outTexCoord.y) * 2), 0.5); // Set the fragment color to orange
}