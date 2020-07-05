#version 330 core

in vec2 UVs;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D text;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, UVs).r);
    FragColor = vec4(color, 1.0) * sampled;
}
