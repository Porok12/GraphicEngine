#version 330 core

out vec4 FragColor;

in vec2 TexPos;

uniform sampler2D myTexture;

void main() {
    vec3 result = texture(myTexture, TexPos).rgb;
    FragColor = vec4(result, 1.0);
}