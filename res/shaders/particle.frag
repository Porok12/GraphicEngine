#version 330 core

in vec2 currentTexCoord;
in vec2 nextTextCoord;
in float factor;

out vec4 FragColor;

uniform sampler2D sprite;

void main() {
    vec4 texColor = mix(texture(sprite, currentTexCoord), texture(sprite, nextTextCoord), factor);
//    if(texColor.a < 0.01)
//        discard;
    FragColor = texColor;
}
