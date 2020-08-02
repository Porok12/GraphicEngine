#version 330 core

out vec4 FragColor;

in vec2 TexPos;
in vec3 debug;

uniform sampler2D myTexture;

void main() {
    vec3 color = texture(myTexture, TexPos).rgb;
    FragColor = vec4(color, 1.0);
}