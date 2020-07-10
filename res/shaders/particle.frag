#version 330 core

in vec4 color;
in vec2 UVs;
in vec2 UVs2;

out vec4 FragColor;

uniform sampler2D sprite;
uniform float factor;

void main() {
    FragColor = (mix(texture(sprite, UVs), texture(sprite, UVs2), factor) * vec4(color));
//    FragColor = (vec4(1.0f) * vec4(color));
}
