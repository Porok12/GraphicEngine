#version 330 core

in vec2 currentTexCoord;
in vec2 nextTextCoord;
in float factor;

out vec4 FragColor;

uniform sampler2D sprite;

void main() {
    FragColor = mix(texture(sprite, currentTexCoord), texture(sprite, nextTextCoord), factor);
}
