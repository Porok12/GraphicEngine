#version 330 core

in vec4 color;
in vec2 UVs;

out vec4 FragColor;

uniform sampler2D sprite;

void main() {
    FragColor = (texture(sprite, UVs) * vec4(color));
}
