#version 330 core

out vec4 FragColor;

in vec2 UVs;

uniform sampler2D texture_diffuse1;

void main() {
    FragColor = vec4(texture(texture_diffuse1, UVs).rgb, 1.0);
}
